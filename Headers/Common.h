#ifndef COMMON_H
#define COMMON_H

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

#endif
