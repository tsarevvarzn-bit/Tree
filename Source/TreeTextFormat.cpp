#include "..\Headers\TreeTextFormat.h"

return_codes printTreeInFile(const node_t* const root_p, const char* const name_of_out_file){

    assert(name_of_out_file);

    FILE* out_file_p = fopen(name_of_out_file, "w");

    if(out_file_p == NULL){

        printf(RED "ERROR: can't open a file with name: <%s>\n" DEFAULT, name_of_out_file);
        return RET_ERROR;
    }

    printSubtreeInFile(root_p, out_file_p);

    fprintf(out_file_p, "\n");

    fclose(out_file_p);

    return RET_CORRECT;
}

void printSubtreeInFile(const node_t* const root_p, FILE* const out_file_p){

    assert(out_file_p);

    if(root_p == NULL){

        fprintf(out_file_p, "(nil)");
        return;

    }else{

        fprintf(out_file_p, "(%d", root_p->value);

        printSubtreeInFile(root_p->left_p, out_file_p);

        printSubtreeInFile(root_p->right_p, out_file_p);

        fprintf(out_file_p, ")");

    }
}

return_codes createTreeFromFile(node_t** const root_p_p, const char* const name_of_in_file){

    assert(root_p_p);
    assert(name_of_in_file);

    int    in_file_descr = open(name_of_in_file, _O_BINARY | _O_RDONLY);

    if(in_file_descr == EOF){

        printf(RED "ERROR: can't open a file with name: <%s>\n" DEFAULT, name_of_in_file);
        return RET_ERROR;
    }

    struct stat file_stats = {};
    fstat(in_file_descr, &file_stats);

    char* tree_text  = (char*) calloc(file_stats.st_size, sizeof(char));

    if(tree_text == NULL){

        printf(RED "ERROR: can't allocate enough memory to read input file with size: %lu byte\n" DEFAULT, file_stats.st_size);
        return RET_ERROR;
    }

    read(in_file_descr, tree_text, file_stats.st_size);


    startProcessingFile(root_p_p, tree_text);


    close(in_file_descr);

    return RET_CORRECT;
}

return_codes startProcessingFile(node_t** const root_p_p, const char* const tree_text){

    assert(root_p_p);
    assert(tree_text);

    int    root_value = 0;
    size_t symbol_idx = 1;

    sscanf(tree_text + 1, "%d", &root_value);

    while(tree_text[symbol_idx++] != '('){

    }

    if(createNode(root_p_p, root_value) == RET_ERROR){

        printf(RED "ERROR: can't create a root of tree from file\n" DEFAULT);
        return RET_ERROR;
    }

    return createSubtreeFromFile(*root_p_p, tree_text, &symbol_idx);
}

return_codes createSubtreeFromFile(node_t* const parent_p, const char* const tree_text, size_t* const symbol_idx_p){

    assert(symbol_idx_p);
    assert(tree_text);


    printf("\n\nTEXT NOW: <%s>, symbol: %llu\n", tree_text, *symbol_idx_p);

    processBrunch(parent_p, tree_text, symbol_idx_p, BRANCH_LEFT );

    processBrunch(parent_p, tree_text, symbol_idx_p, BRANCH_RIGHT);

    return RET_CORRECT;
}

return_codes processBrunch(node_t* const parent_p, const char* const tree_text, size_t* const symbol_idx_p, const branch_codes branch_code){

    assert(parent_p);
    assert(symbol_idx_p);
    assert(tree_text);

    int node_value = 0;

    node_t** node_p_p = getBranchPointer(parent_p, branch_code);

    if(strncmp(tree_text + *symbol_idx_p, "nil)", 4) == 0){

        *node_p_p = NULL;
        *symbol_idx_p += 4;

        while(tree_text[(*symbol_idx_p)++] != '('){

        }

    }else{

        if(sscanf(tree_text + *symbol_idx_p, "%d", &node_value) != 1){// Парсим значение левого, если оно некорректное - ошибка

            printf(RED "ERROR: incorrect text format of tree in file symbol idx: %llu\n" DEFAULT, *symbol_idx_p);

            return RET_ERROR;
        }

        printf("Create right kid of %d, %d\n", parent_p->value, node_value);

        createSheet(parent_p, branch_code, node_value);// TODO проверка

        while(tree_text[(*symbol_idx_p)++] != '('){

        }

        createSubtreeFromFile(*node_p_p, tree_text, symbol_idx_p);
    }

    return RET_CORRECT;
}

