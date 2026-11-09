#include "..\Headers\Visualization.h"

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
