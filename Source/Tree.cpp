#include "..\Headers\Tree.h"


return_codes createSheet(node_t* const parent_p, branch_codes branch_code, int value){

    assert(parent_p);

    node_t** new_node_p_p = NULL;

    switch(branch_code){

        case BRANCH_LEFT:

            new_node_p_p = &parent_p->left_p;
            break;

        case BRANCH_RIGHT:

            new_node_p_p = &parent_p->right_p;
            break;

        default:

            printf(RED "ERROR: incorrect code of parent branch: %d\n" DEFAULT, branch_code);
            return RET_ERROR;
    }

    if(createNode(new_node_p_p, value) == RET_ERROR){

        return RET_ERROR;
    }

    (*new_node_p_p)->parent_p = parent_p;

    return RET_CORRECT;
}

return_codes createNode(node_t** const root_p_p, int value){

    assert(root_p_p);

    if(*root_p_p != NULL){

        printf(RED "ERROR: there is already a node following this pointer: [%p]\n" DEFAULT, *root_p_p);
        return RET_ERROR;
    }

    *root_p_p = (node_t*) calloc(1, sizeof(node_t));

    if(*root_p_p == NULL){

        printf(RED "ERROR: no way to allocate memory for new root\n" DEFAULT);
        return RET_ERROR;
    }

    (*root_p_p)->parent_p = NULL ;
    (*root_p_p)->value    = value;
    (*root_p_p)->left_p   = NULL ;
    (*root_p_p)->right_p  = NULL ;

    return RET_CORRECT;
}

return_codes deleteNode(node_t* const node_p){

    assert(node_p);

    if(node_p->left_p != NULL || node_p->right_p != NULL){

        printf(RED "ERROR: node for delete: %p have branches: left: %p, right: %p, delete them first!\n",
        node_p, node_p->left_p, node_p->right_p);

        return RET_ERROR;
    }

    free(node_p);

    return RET_CORRECT;
}

return_codes deleteSheet(node_t* const parent_p, branch_codes branch_code){

    assert(parent_p);

    node_t** new_node_p_p = NULL;

    switch(branch_code){

        case BRANCH_LEFT:

            new_node_p_p = &parent_p->left_p;
            break;

        case BRANCH_RIGHT:

            new_node_p_p = &parent_p->right_p;
            break;

        default:

            printf(RED "ERROR: incorrect code of parent branch: %d\n" DEFAULT, branch_code);
            return RET_ERROR;
    }

    if(deleteNode(*new_node_p_p) == RET_ERROR){

        return RET_ERROR;
    }

    (*new_node_p_p) = NULL;

    return RET_CORRECT;
}

node_t** getBranchPointer(node_t * parent_p, const branch_codes branch_code){

    assert(parent_p);

    switch(branch_code){

        case BRANCH_LEFT:

            return &(parent_p->left_p);
            break;

        case BRANCH_RIGHT:

            return &(parent_p->right_p);
            break;

        default:

            printf(RED "ERROR: incorrect enum value in getBrunchPointer function: %d\n" DEFAULT, branch_code);
            return NULL;
    }
}
