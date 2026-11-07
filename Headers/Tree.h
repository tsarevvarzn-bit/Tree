#ifndef TREE_H
#define TREE_H


#include <stdio.h>
#include <assert.h>

#include "Colors.h"

struct node_t{

    node_t* parent_p;
    node_t* left_p  ;
    node_t* right_p ;
    int     value   ;
};

enum return_codes{

    RET_ERROR,
    RET_CORRECT
};

enum branch_codes{

    BRANCH_LEFT,
    BRANCH_RIGHT
};

return_codes createRoot(node_t** const root_p_p, int value);

return_codes createNode        (node_t* const parent_p, branch_codes branch_code, int value);
void         printTreeInConsole(const node_t* const root_p);
#endif
