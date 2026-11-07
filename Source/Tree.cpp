#include "..\Headers\Tree.h"

int main(){

    node_t* root_p = NULL;

    createRoot(&root_p, 1);
    printTreeInConsole(root_p); putchar('\n');

    createNode(root_p, BRANCH_LEFT, -10);
    printTreeInConsole(root_p); putchar('\n');
    createNode(root_p, BRANCH_RIGHT, 10);
    printTreeInConsole(root_p); putchar('\n');
    createNode(root_p->right_p, BRANCH_RIGHT, 15);
    printTreeInConsole(root_p); putchar('\n');
}

return_codes createRoot(node_t** const root_p_p, int value){

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

return_codes createNode(node_t* const parent_p, branch_codes branch_code, int value){

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

    if(*new_node_p_p != NULL){

        printf(RED "ERROR: there is already a node following this pointer: [%p]\n" DEFAULT, *new_node_p_p);
        return RET_ERROR;
    }

    *new_node_p_p = (node_t*) calloc(1, sizeof(node_t));

    if(*new_node_p_p == NULL){

        printf(RED "ERROR: no way to allocate memory for new node\n" DEFAULT);
        return RET_ERROR;
    }

    (*new_node_p_p)->parent_p = parent_p;
    (*new_node_p_p)->value    = value   ;
    (*new_node_p_p)->left_p   = NULL    ;
    (*new_node_p_p)->right_p  = NULL    ;

    return RET_CORRECT;
}

void printTreeInConsole(const node_t* const root_p){

    if(root_p == NULL){

        printf("(nil)");
        return;
    }

    printf("(%d", root_p->value);

    printTreeInConsole(root_p->left_p);

    printTreeInConsole(root_p->right_p);

    printf(")");

    // printf("Node" CYAN "[%p]" DEFAULT ", parent" CYAN "[%p]" DEFAULT ", value: " YELLOW "%d" DEFAULT
    //        ", left branch" CYAN "[%p]" DEFAULT ", right" CYAN "[%p]" DEFAULT,
    //        root_p, root_p->value, root_p->left_p, root_p->right_p);
    //
    // if(root_p->left)
}
