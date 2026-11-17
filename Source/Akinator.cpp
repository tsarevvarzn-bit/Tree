#include "..\Headers\Akinator.h"

void startAkinator(node_t* root_p){

    assert(root_p);

    printf("\nHi! I'm an AI running locally on your computer, guess any human related to MIPT and I'll guess it!");

    getchar();

    branch_codes branch_code = BRANCH_LEFT;

    while(root_p->left_p != NULL && root_p->right_p != NULL){

        printf("Next question: " YELLOW "%s" DEFAULT " Enter y/n:", root_p->value);

        if(getchar() == 'y'){

            root_p = root_p->left_p;
            branch_code = BRANCH_LEFT;

        }else{

            root_p = root_p->right_p;
            branch_code = BRANCH_RIGHT;
        }

        getchar();
    }

    printf("YOU HAVE MADE A WISH: " YELLOW "%s" DEFAULT ", isn't it? y/n:", root_p->value);

    if(getchar() == 'y'){

        getchar();
        printf("\nI know it...\n");

    }else{

        getchar();
        trainAkinator(root_p, branch_code);
    }
}

void trainAkinator(node_t* root_p, branch_codes branch_code){

    assert(root_p);

    char new_object_name   [MAX_STR_LEN] = "";
    char new_question_value[MAX_STR_LEN] = "";


    printf("\n... Ok, let's make sure I guess next time. So, enter the name of the object you have hidden:");

    scanf("%[^\n]", new_object_name   ); getchar();

    printf("\nHow is %s different from %s? %s is:", new_object_name, root_p->value, new_object_name);

    scanf("%[^\n]", new_question_value); getchar();

    strcat(new_question_value, "?");


    node_t* parent_of_new_question_p = root_p->parent_p;


    deleteSheet(parent_of_new_question_p, branch_code);

    createSheet(parent_of_new_question_p        , branch_code , new_question_value);

    node_t* new_question_p = *getBranchPointer(parent_of_new_question_p, branch_code);

    createSheet(new_question_p, BRANCH_LEFT , new_object_name );

    createSheet(new_question_p, BRANCH_RIGHT, root_p->value   );
}

void compareTwoObjects(node_t* root_p){

    assert(root_p);

    size_t first_path  = 0;
    size_t second_path = 0;

    char first_object_name [MAX_STR_LEN] = "";
    char second_object_name[MAX_STR_LEN] = "";

    printf("\nPrint name of first object:");
    scanf("%[^\n]", first_object_name); getchar();

    printf("\nPrint name of second object:");
    scanf("%[^\n]", second_object_name); getchar();

    getPathToTheObject(root_p, first_object_name , &first_path );
    getPathToTheObject(root_p, second_object_name, &second_path);

    printf("\n%s and %s the " BLUE "same" DEFAULT " in:\n", first_object_name, second_object_name);

    size_t difference = first_path ^ second_path;
    unsigned char depth = 0;


    while((difference & ((size_t)1 << depth)) == 0 && root_p->left_p != NULL && root_p->right_p != NULL){

        if(first_path & ((size_t)1 << depth)){

            printf("%s - " YELLOW "Yes\n" DEFAULT, root_p->value);
            root_p = root_p->left_p;

        }else{

            printf("%s - " YELLOW "No\n" DEFAULT, root_p->value);
            root_p = root_p->right_p;
        }

        depth++;
    }

    printf("\nBut " BLUE "%s" DEFAULT ":\n", first_object_name);

    printObjectCharacteristic(root_p, first_path, depth);

    printf("\nAnd " BLUE "%s" DEFAULT ":\n", second_object_name);

    printObjectCharacteristic(root_p, second_path, depth);
}

void printObjectCharacteristic(const node_t* object_p, size_t const path, unsigned char depth){

    assert(object_p);

    while(object_p->left_p != NULL && object_p->right_p != NULL){

        if(path & ((size_t)1 << depth)){

            printf("%s - " YELLOW "Yes\n" DEFAULT, object_p->value);
            object_p = object_p->left_p;

        }else{

            printf("%s - " YELLOW "No\n" DEFAULT, object_p->value);
            object_p = object_p->right_p;
        }

        depth++;
    }
}

void findAnObject(node_t* root_p){

    char object_name[MAX_STR_LEN] = "";

    printf("\nPrint name of object to find:");

    scanf("%[^\n]", object_name); getchar();

    size_t path = 0;

    if(getPathToTheObject(root_p, object_name, &path) == RET_ERROR){

        return;
    }

    printf("Object full characteristics:\n\n");

    unsigned char depth = 0;
    node_t* node_p = root_p;

    while(node_p->left_p != NULL && node_p->right_p != NULL){

        if(path & ((size_t)1 << depth)){

            printf("%s - " YELLOW "Yes\n" DEFAULT, node_p->value);
            node_p = node_p->left_p;

        }else{

            printf("%s - " YELLOW "No\n" DEFAULT, node_p->value);
            node_p = node_p->right_p;
        }

        depth++;
    }

    printf("\n");
}

return_codes getPathToTheObject(node_t* root_p, const char* const value_of_the_object, size_t* path_p){

    assert(value_of_the_object);
    assert(path_p);

    if(checkSubtreeOnObject(root_p, value_of_the_object, path_p, 0) == 0){

        printf(YELLOW "Can't find object with name: <%s>\n" DEFAULT, value_of_the_object);

        return RET_ERROR;
    }

    return RET_CORRECT;
}

//Налево - 1, направо - 0
//Переписываем биты,

bool checkSubtreeOnObject(node_t* root_p, const char* const object_name, size_t* const path_p, unsigned char node_depth){

    assert(root_p);
    assert(object_name);
    assert(path_p);

    if(strncmp(root_p->value, object_name, MAX_STR_LEN) == 0){

        return 1;
    }

    if(root_p->left_p == NULL || root_p->right_p == NULL){

        return 0;
    }

    if(checkSubtreeOnObject(root_p->left_p, object_name, path_p, node_depth + 1) == 1){

        (*path_p) |= ((size_t)1 << node_depth);

        return 1;
    }

    if(checkSubtreeOnObject(root_p->right_p, object_name, path_p, node_depth + 1) == 1){

        return 1;
    }

    return 0;
}
