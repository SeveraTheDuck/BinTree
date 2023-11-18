#ifndef ANA_BIN_TREE_STRUCT
#define ANA_BIN_TREE_STRUCT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ANA_BinTree_config.h"

typedef size_t ANA_BinTree_error_type;

enum ANA_BinTree_errors
{
    ANA_BINTREE_NO_ERRORS      = 0,
    ANA_BINTREE_STRUCT_NULLPTR = 1 << 1,
    ANA_BINTREE_NODE_NULLPTR   = 1 << 2,
    /* something else? */
    // check cycle?
};

struct ANA_BinTree_node
{
    ANA_BinTree_data_type data;
    ANA_BinTree_node*     left;
    ANA_BinTree_node*     right;
    ANA_BinTree_node*     parent;
};

struct ANA_BinTree
{
    ANA_BinTree_node* root;
    size_t n_elem;

    ANA_BinTree_error_type errors;
};

ANA_BinTree_error_type
ANA_BinTree_Ctor       (      ANA_BinTree*          const tree,
                        const ANA_BinTree_data_type       data);

ANA_BinTree_node*
ANA_BinTree_CtorNode   (const ANA_BinTree_data_type   data,
                              ANA_BinTree_node* const left,
                              ANA_BinTree_node* const right,
                              ANA_BinTree_node* const parent);

ANA_BinTree_error_type
ANA_BinTree_DestroySubtree (ANA_BinTree_node* const node);

ANA_BinTree_node*
ANA_BinTree_InsertSorted (      ANA_BinTree*          const tree,
                          const ANA_BinTree_data_type       data);

void
ANA_BinTree_PrintSubtreePreOrder  (const ANA_BinTree_node* const node);

void
ANA_BinTree_PrintSubtreePostOrder (const ANA_BinTree_node* const node);

void
ANA_BinTree_PrintSubtreeInOrder   (const ANA_BinTree_node* const node);

#endif
