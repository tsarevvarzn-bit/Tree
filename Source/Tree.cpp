#include "..\Headers\Tree.h"

int main(){

    node_t* root_p = NULL;

    createNode(&root_p, 1);
    printTreeInConsole(root_p); putchar('\n');

    createSheet(root_p, BRANCH_LEFT, -10);
    printTreeInConsole(root_p); putchar('\n');
    createSheet(root_p, BRANCH_RIGHT, 10);
    printTreeInConsole(root_p); putchar('\n');
    createSheet(root_p->right_p, BRANCH_RIGHT, 15);
    printTreeInConsole(root_p); putchar('\n');
    createSheet(root_p->right_p->right_p, BRANCH_RIGHT, 25);
    printTreeInConsole(root_p); putchar('\n');
    createSheet(root_p->right_p->right_p, BRANCH_LEFT, 13);
    printTreeInConsole(root_p); putchar('\n');


    //createSheet(&root_p->right_p)

    visualizeTree(root_p, "labuba.svg");
}

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

void printTreeInConsole(const node_t* const root_p){

    if(root_p == NULL){

        printf("(nil)");
        return;
    }

    printf("(%d", root_p->value);

    printTreeInConsole(root_p->left_p);

    printTreeInConsole(root_p->right_p);

    printf(")");
}

void visualizeTree(const node_t* const root_p, const char * const name_of_file){

    assert(root_p);
    assert(name_of_file);

    FILE* out_dot_file_p = fopen("DataForVisualization.dot", "w");


    fprintf(out_dot_file_p,

    "digraph {\n"
    "\n"
    "    graph [\n"
    "        rankdir=TB,\n"
    "        splines=true,\n"
    "        overlap=true,\n"
    "        nodesep=0.5,\n"
    "        ranksep=0.8,\n"
    "        bgcolor=\"#312d4b\"\n"
    "    ]\n"
    "\n"
    "    edge [\n"
    "        penwidth=5,\n"
    "        arrowhead=\"vee\",\n"
    "        color=\"#0e6fbe\",\n"
    "    ]\n"
    "\n"
    "    node [shape=plain]\n"

    );

    addTreeToVisualization(root_p, out_dot_file_p);

    fprintf(out_dot_file_p, "}");


    fclose(out_dot_file_p);

    char str_for_system_call[MAX_LEN_OF_STR_FOR_SYSTEM_CALL] = "";

    sprintf(str_for_system_call, "dot.exe -Tsvg DataForVisualization.dot -o %s", name_of_file);

    int result = system(str_for_system_call);

    if(result == SYSTEM_CORRECT_RETURN){

        printf(GREEN "Correct visualization! Look for a visualization file named " YELLOW "\"%s\"\n" DEFAULT, name_of_file);

    }else{

        printf(RED "ERROR! Incorrect return of\n"     \
                   "int result = system(%s);\n"       \
                   "result: %d" DEFAULT, str_for_system_call, result);
    }


}

void addTreeToVisualization(const node_t* const root_p, FILE* const out_file_p){

    assert(root_p);
    assert(out_file_p);

    fprintf(out_file_p,

    "    \"%p\" [label=<\n"
    "        <TABLE BORDER=\"2\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#9975bf\">\n"
    "            <TR><TD COLSPAN=\"3\" PORT=\"parent\">parent = %p</TD></TR>\n"
    "            <TR><TD COLSPAN=\"3\" BGCOLOR = \"yellow\">value = %d</TD></TR>\n"
    "            <TR>\n"
    "                <TD PORT=\"left\">left = %p</TD>\n"
    "                <TD>pointer = %p</TD>\n"
    "                <TD PORT=\"right\">right = %p</TD>\n"
    "            </TR>\n"
    "        </TABLE>\n"
    "    >];\n",

    root_p, root_p->parent_p, root_p->value, root_p->left_p, root_p, root_p->right_p);


    if(root_p->left_p == NULL && root_p->right_p == NULL){

        return;
    }

    if(root_p->left_p == NULL){

        addTreeToVisualization(root_p->right_p, out_file_p);
        fprintf(out_file_p, "\"%p\":right->\"%p\"\n", root_p, root_p->right_p);
        return;
    }

    if(root_p->right_p == NULL){

        addTreeToVisualization(root_p->left_p, out_file_p);
        fprintf(out_file_p, "\"%p\":left->\"%p\"\n", root_p, root_p->left_p);
        return;
    }

    addTreeToVisualization(root_p->left_p , out_file_p);
    addTreeToVisualization(root_p->right_p, out_file_p);

    fprintf(out_file_p, "\"%p\":left->\"%p\"\n" , root_p, root_p->left_p );
    fprintf(out_file_p, "\"%p\":right->\"%p\"\n", root_p, root_p->right_p);

    fprintf(out_file_p, "{rank=same; \"%p\"; \"%p\"}\n", root_p->left_p, root_p->left_p);
}
