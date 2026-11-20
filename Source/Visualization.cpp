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
    "        nodesep=1,\n"
    "        ranksep=0.8,\n"
    "        bgcolor=\"#312d4b\"\n"
    "    ]\n"
    "\n"
    "    edge [\n"
    "        penwidth=5,\n"
    "        color=\"#0e6fbe\",\n"
    "    ]\n"
    "\n"
    "    node [\n"
    "        shape = Mrecord,\n"
    "        style = filled,\n"
    "        fillcolor = \"yellow\"\n"
    "    ]\n"

    );

    addTreeToVisualization(root_p, out_dot_file_p);

    fprintf(out_dot_file_p, "}");


    fclose(out_dot_file_p);

    char str_for_system_call[MAX_LEN_OF_STR_FOR_SYSTEM_CALL] = "";

    sprintf(str_for_system_call, "dot.exe -Tsvg DataForVisualization.dot -o %s", name_of_file);

    int result = system(str_for_system_call);

    if(result == SYSTEM_CORRECT_RETURN){

        printf(GREEN "Correct visualization! Look for a visualization file named " YELLOW "\"%s\"\n" DEFAULT, name_of_file);

        FILE* log_file_p = fopen(LOG_MD_FILE_NAME, "a");

        fprintf(log_file_p, "## Visualization of tree:\n![](%s)\n\n", name_of_file);

        fclose(log_file_p);

    }else{

        printf(RED "ERROR! Incorrect return of\n"     \
                   "int result = system(%s);\n"       \
                   "result: %d" DEFAULT, str_for_system_call, result);
    }

}

void addTreeToVisualization(const node_t* const root_p, FILE* const out_file_p){

    assert(root_p);
    assert(out_file_p);

    if(root_p->left_p == NULL && root_p->right_p == NULL){

        fprintf(out_file_p,

    "    node [\n"
    "        fillcolor = \"#69bc66\"\n"
    "    ]\n"
        );

    }else{

        fprintf(out_file_p,

    "    node [\n"
    "        fillcolor = \"yellow\"\n"
    "    ]\n"
        );

    }

    ON_DEBUG(
    fprintf(out_file_p,

    "    \"%p\" [label= \"{ <parent> parent = \\\"%p\\\" |\n"
    "           value = %s | \n"
    "           { <left> left = \\\"%p\\\"| pointer = \\\"%p\\\" | <right> right = \\\"%p\\\"}}\"]\n\n",

    root_p, root_p->parent_p, root_p->value, root_p->left_p, root_p, root_p->right_p);
    )

    OFF_DEBUG(
    fprintf(out_file_p,

    "    \"%p\" [label = \" %s\"]\n\n",

    root_p, root_p->value);
    )

    if(root_p->left_p == NULL && root_p->right_p == NULL){

        return;
    }

    if(root_p->left_p == NULL){

        addTreeToVisualization(root_p->right_p, out_file_p);
        ON_DEBUG( fprintf(out_file_p, "   \"%p\":right->\"%p\"\n", root_p, root_p->right_p);)
        OFF_DEBUG(fprintf(out_file_p, "   \"%p\"->\"%p\"\n", root_p, root_p->right_p);)
        return;
    }

    if(root_p->right_p == NULL){

        addTreeToVisualization(root_p->left_p, out_file_p);
        ON_DEBUG( fprintf(out_file_p, "   \"%p\":left->\"%p\"\n", root_p, root_p->left_p);)
        OFF_DEBUG(fprintf(out_file_p, "   \"%p\"->\"%p\"\n", root_p, root_p->left_p);)
        return;
    }

    addTreeToVisualization(root_p->left_p , out_file_p);
    addTreeToVisualization(root_p->right_p, out_file_p);

    ON_DEBUG( fprintf(out_file_p, "   \"%p\":left->\"%p\"[label = \"YES\", fontcolor = \"white\"]\n" , root_p, root_p->left_p );)
    OFF_DEBUG(fprintf(out_file_p, "   \"%p\"->\"%p\"[label = \"YES\", fontcolor = \"white\"]\n"      , root_p, root_p->left_p );)
    ON_DEBUG( fprintf(out_file_p, "   \"%p\":right->\"%p\"[label = \"NO\", fontcolor = \"white\"]\n" , root_p, root_p->right_p);)
    OFF_DEBUG(fprintf(out_file_p, "   \"%p\"->\"%p\"[label = \"NO\", fontcolor = \"white\"]\n"       , root_p, root_p->right_p);)

    fprintf(out_file_p, "   {rank=same; \"%p\"; \"%p\"}\n", root_p->left_p, root_p->left_p);
}
