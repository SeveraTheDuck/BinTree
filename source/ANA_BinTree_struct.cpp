#include "../include/ANA_BinTree_struct.h"

ANA_BinTree_error_type
ANA_BinTree_Ctor       (      ANA_BinTree*          const tree,
                        const ANA_BinTree_data_type       data)
{
    if (!tree)
    {
        fprintf (stderr, "Invalid pointer to tree struct: [%p]", tree);
        return ANA_BINTREE_STRUCT_NULLPTR;
    }

    for (size_t allocated_data_index = 0;
                allocated_data_index < MAX_NUM_OF_ALLOCATED_DATA;
                allocated_data_index++)
    {
        tree->allocated_data [allocated_data_index] = ANA_BinTree_POISON;
    }

    tree->root = ANA_BinTree_CtorNode (data, nullptr, nullptr, nullptr);
    if (!tree->root)
    {
        tree->errors |= ANA_BINTREE_NODE_NULLPTR;
        return tree->errors;
    }

    tree->n_elem = 1;
    return tree->errors;
}

ANA_BinTree_node*
ANA_BinTree_CtorNode   (const ANA_BinTree_data_type   data,
                              ANA_BinTree_node* const left,
                              ANA_BinTree_node* const right,
                              ANA_BinTree_node* const parent)
{
    ANA_BinTree_node* new_node = (ANA_BinTree_node*)
               calloc (1, sizeof (ANA_BinTree_node));
    if (!new_node)
    {
        perror ("new_node calloc error");
        return nullptr;
    }

    new_node->data   = data;
    new_node->left   = left;
    new_node->right  = right;
    new_node->parent = parent;

    return new_node;
}

ANA_BinTree_error_type
ANA_BinTree_DestroySubtree (ANA_BinTree_node* const node)
{
    if (!node)
    {
        return ANA_BINTREE_NODE_NULLPTR;
    }

    ANA_BinTree_DestroySubtree (node->left);
    ANA_BinTree_DestroySubtree (node->right);

    node->data  = ANA_BinTree_POISON;
    node->left  = nullptr;
    node->right = nullptr;

    if (node->parent)
    {
        if (node == node->parent->left)
        {
            node->parent->left  = nullptr;
        }

        else
        {
            node->parent->right = nullptr;
        }

        node->parent = nullptr;
    }

    free (node);

    return ANA_BINTREE_NO_ERRORS;
}

ANA_BinTree_node*
ANA_BinTree_InsertSorted (      ANA_BinTree*          const tree,
                          const ANA_BinTree_data_type       data)
{
    if (!tree)
    {
        fprintf (stderr, "Invalid pointer to tree struct: [%p]", tree);
        return nullptr;
    }

    if (!tree->root)
    {
        fprintf (stderr, "Invalid pointer to tree root: [%p]", tree->root);
        return nullptr;
    }

    ANA_BinTree_node* node = tree->root;

    ANA_BinTree_node* new_node =
        ANA_BinTree_CtorNode (data, nullptr, nullptr, nullptr);

    while (true)
    {
        if (data <= node->data)
        {
            if (!node->left)
            {
                node->left = new_node;
                break;
            }
            node = node->left;
        }

        else
        {
            if (!node->right)
            {
                node->right = new_node;
                break;
            }
            node = node->right;
        }
    }

    new_node->parent = node;

    return new_node;
}

void
ANA_BinTree_PrintSubtreePreOrder (const ANA_BinTree_node* const node)
{
    if (!node)
    {
        printf ("nil ");
        return;
    }

    printf ("( ");

    printf (ANA_BinTree_OUTPUT_F " ", node->data);
    ANA_BinTree_PrintSubtreePreOrder (node->left);
    ANA_BinTree_PrintSubtreePreOrder (node->right);

    printf (") ");
}

void
ANA_BinTree_PrintSubtreePostOrder (const ANA_BinTree_node* const node)
{
    if (!node)
    {
        printf ("nil ");
        return;
    }

    printf ("( ");

    ANA_BinTree_PrintSubtreePostOrder (node->left);
    ANA_BinTree_PrintSubtreePostOrder (node->right);
    printf (ANA_BinTree_OUTPUT_F " ", node->data);

    printf (") ");
}

void
ANA_BinTree_PrintSubtreeInOrder (const ANA_BinTree_node* const node)
{
    if (!node)
    {
        printf ("nil ");
        return;
    }

    printf ("( ");

    ANA_BinTree_PrintSubtreeInOrder (node->left);
    printf (ANA_BinTree_OUTPUT_F " ", node->data);
    ANA_BinTree_PrintSubtreeInOrder (node->right);

    printf (") ");
}
