#include "..\Headers\Main.h"

int main(){

    node_t* root_p = NULL;

    createTreeFromFile(&root_p, "Tree1.txt");

    bool is_continue = true;

    while(is_continue){

        printf("What do you want to do? "
                YELLOW "1" DEFAULT " - save and continue guessing, "  YELLOW "2" DEFAULT " - don't save and continue, " YELLOW "3" DEFAULT " - save new tree in file and exit, "
                YELLOW "4" DEFAULT " - don't save changes and exit, " YELLOW "5" DEFAULT " - find an object, "          YELLOW "6" DEFAULT "  - compare two objects, "
                YELLOW "7" DEFAULT " - visualize:");

        int command = getchar(); getchar();

        switch(command){

            case '1':

                printTreeInFile(root_p, "Tree1.txt");
                startAkinator(root_p);
                break;

            case '2':

                startAkinator(root_p);
                break;

            case '3':

                is_continue = false;
                printTreeInFile(root_p, "Tree1.txt");
                break;

            case '4':

                is_continue = false;
                break;

            case '5':

                findAnObject(root_p);
                break;

            case '6':

                compareTwoObjects(root_p);
                break;

            case '7':

                printf("Ok, let's visualize tree after guessing\n");
                visualizeTree(root_p, "TreeViz.svg");
                break;

            default:

                printf(RED "\nIncorrect format of command! Start doing command 4\n" DEFAULT);
                is_continue = false;
        }
    }
}

void startAkinator(node_t* root_p){

    assert(root_p);

    printf("\nHi! I'm an AI running locally on your computer, guess any object related to MIPT and I'll guess it!");

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

    node_t* node_first_p  = root_p;
    node_t* node_second_p = root_p;

    unsigned char depth_first  = depth;
    unsigned char depth_second = depth;

    printf("\nBut " BLUE "%s" DEFAULT ":\n", first_object_name);

    while(node_first_p->left_p != NULL && node_first_p->right_p != NULL){

        if(first_path & ((size_t)1 << depth_first)){

            printf("%s - " YELLOW "Yes\n" DEFAULT, node_first_p->value);
            node_first_p = node_first_p->left_p;

        }else{

            printf("%s - " YELLOW "No\n" DEFAULT, node_first_p->value);
            node_first_p = node_first_p->right_p;
        }

        depth_first++;
    }

    printf("\nAnd " BLUE "%s" DEFAULT ":\n", second_object_name);

    while(node_second_p->left_p != NULL && node_second_p->right_p != NULL){

        if(second_path & ((size_t)1 << depth_second)){

            printf("%s - " YELLOW "Yes\n" DEFAULT, node_second_p->value);
            node_second_p = node_second_p->left_p;

        }else{

            printf("%s - " YELLOW "No\n" DEFAULT, node_second_p->value);
            node_second_p = node_second_p->right_p;
        }

        depth_second++;
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

    print_bits(path);
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

void print_bits(size_t x)
{
    const int bits = (int)(sizeof(size_t) * CHAR_BIT);
    for (int i = bits - 1; i >= 0; --i) {
        putchar((x >> i) & (size_t)1 ? '1' : '0');
        /* для читаемости можно вставлять пробел каждые 4 бита */
        if (i % 4 == 0 && i != 0) putchar(' ');
    }
    putchar('\n');
}
