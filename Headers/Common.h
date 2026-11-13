#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Colors.h"

const int MAX_STR_LEN = 100;

struct node_t{

    node_t* parent_p;
    node_t* left_p  ;
    node_t* right_p ;

    char value[MAX_STR_LEN];
};

enum return_codes{

    RET_ERROR,
    RET_CORRECT
};

enum branch_codes{

    BRANCH_LEFT,
    BRANCH_RIGHT
};

#ifdef DEBUG

    #define ON_DEBUG(...) __VA_ARGS__

#else

    #define ON_DEBUG(...)

#endif

#endif
