#include "..\Headers\Main.h"

int main(){

    node_t* root_p = NULL;

    createTreeFromFile(&root_p, "Tree1.txt");

    bool is_guessing = true;

    visualizeTree(root_p, "labuba3.svg");

    while(is_guessing){

        startAkinator(root_p);

        printf("Ok, let's visualize tree after guessing\n");

        visualizeTree(root_p, "labuba3.svg");

        printf("What do you want to do? 1 - save and continue guessing, 2 - don't save and continue, 2 - save new tree in file and exit, 4 - don't save changes and exit:");

        int command = getchar(); getchar();

        switch(command){

            case '1':

                printTreeInFile(root_p, "Tree1.txt");
                break;

            case '2':

                break;

            case '3':

                is_guessing = false;
                printTreeInFile(root_p, "Tree1.txt");
                break;

            case '4':

                is_guessing = false;
                break;

            default:

                printf(RED "\nIncorrect format of command! Start doing command 4\n");
                is_guessing = false;
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

        getchar();// Берем /n
    }

    printf("YOU HAVE MADE A WISH: " YELLOW "%s" DEFAULT ", isn't it? y/n:", root_p->value);

    if(getchar() == 'y'){

        getchar();
        printf("\nI know it...\n");

    }else{

        getchar();
        printf("\n... Ok, let's make sure I guess next time. So, enter the name of the object you have hidden:");

        char new_object_name[MAX_STR_LEN] = "";

        scanf("%[^\n]", new_object_name); getchar();

        printf("\nHow is %s different from %s? %s is:", new_object_name, root_p->value, new_object_name);

        char new_question_value[MAX_STR_LEN] = "";

        scanf("%[^\n]", new_question_value); getchar();

        strcat(new_question_value, "?");

        // TODO корень менять не можем

        node_t* parent_of_new_question_p = root_p->parent_p;//Sportsmen?

        char old_object_name[MAX_STR_LEN] = "";

        strncpy(old_object_name, root_p->value, MAX_STR_LEN);



        deleteSheet(parent_of_new_question_p, branch_code);

        createSheet(parent_of_new_question_p        , branch_code , new_question_value);

        node_t* new_question_p = *getBranchPointer(parent_of_new_question_p, branch_code);

        createSheet(new_question_p, BRANCH_LEFT , new_object_name   );

        createSheet(new_question_p, BRANCH_RIGHT, old_object_name   );
    }
}
