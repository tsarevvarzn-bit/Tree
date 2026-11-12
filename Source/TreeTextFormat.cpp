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
    size_t symbol_idx    = 0;

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

    int root_value = 0;

    sscanf(tree_text + 1, "%d", &root_value);

    symbol_idx = 1;

    printf("%llu", symbol_idx);

    while(tree_text[symbol_idx++] != '('){

        printf("%c\n", tree_text[symbol_idx]);

    }//Проскипали до первого аргумента

    printf("%llu", symbol_idx);

    createNode(root_p_p, root_value);//TODO проверка

    //printf("2");
    printf("%llu", symbol_idx);

    printf("\n\nFIRST TEXT NOW: <%s>, symbol: %llu>", tree_text, symbol_idx);

    createSubtreeFromFile(*root_p_p, tree_text, &symbol_idx);

    //printf("3");

    close(in_file_descr);

    return RET_CORRECT;
}

return_codes createSubtreeFromFile(node_t* const parent_p, char* const tree_text, size_t* const symbol_idx_p){

    assert(symbol_idx_p);
    assert(tree_text);

    //printf("4\n");

    printf("\n\nTEXT NOW: <%s>, symbol: %llu\n", tree_text, *symbol_idx_p);

    int value_left  = 0;
    int value_right = 0;

    if(strncmp(tree_text + *symbol_idx_p, "nil)", 4) == 0){// Если левый ребенок - ноль

        parent_p->left_p = NULL;
        *symbol_idx_p += 4;

        while(tree_text[(*symbol_idx_p)++] != '('){

        }//Проскипали до первого аргумента

        printf("NUL_L\n");

    }else{

        if(sscanf(tree_text + *symbol_idx_p, "%d", &value_left) != 1){// Парсим значение левого, если оно некорректное - ошибка

            printf(RED "ERROR: incorrect text format of tree in file with name: <%s>, symbol idx: %llu\n" DEFAULT,
            "TODOODODO", *symbol_idx_p);

            return RET_ERROR;
        }

        printf("Create left kid of %d, %d\n", parent_p->value, value_left);
        createSheet(parent_p, BRANCH_LEFT, value_left);//TODO проверка

        while(tree_text[(*symbol_idx_p)++] != '('){

        }//Проскипали до первого аргумента

        createSubtreeFromFile(parent_p->left_p, tree_text, symbol_idx_p);//Обрабатываем это поддерево
    }


    // printf("Process")



    if(strncmp(tree_text + *symbol_idx_p, "nil)", 4) == 0){// Если левый ребенок - ноль

        parent_p->right_p = NULL;
        *symbol_idx_p += 4;

        while(tree_text[(*symbol_idx_p)++] != '('){

        }//Проскипали до первого аргумента

        printf("NUL_L\n");

    }else{

        if(sscanf(tree_text + *symbol_idx_p, "%d", &value_right) != 1){// Парсим значение левого, если оно некорректное - ошибка

            printf(RED "ERROR: incorrect text format of tree in file with name: <%s>, symbol idx: %llu\n" DEFAULT,
            "TODOODODO", *symbol_idx_p);

            return RET_ERROR;
        }

        printf("Create right kid of %d, %d\n", parent_p->value, value_right);
        createSheet(parent_p, BRANCH_RIGHT, value_right);//TODO проверка

        while(tree_text[(*symbol_idx_p)++] != '('){

        }//Проскипали до первого аргумента

        createSubtreeFromFile(parent_p->right_p, tree_text, symbol_idx_p);//Обрабатываем это поддерево
    }



    return RET_CORRECT;
}
