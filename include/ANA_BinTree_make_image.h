#ifndef ANA_BIN_TREE_MAKE_IMAGE_H
#define ANA_BIN_TREE_MAKE_IMAGE_H

#include "ANA_BinTree_struct.h"

void
MakeTreeImage (const ANA_BinTree* const tree);

void
PrintNodes (const ANA_BinTree_node* const node,
                  FILE*             const image_file);

#endif
