#include "..\Headers\Main.h"

int main(){

    node_t* root_p = NULL;

    FILE* log_file_p = fopen(LOG_MD_FILE_NAME, "w");
    fprintf(log_file_p, "\n\n# New log, start to read the file:\n");
    fclose(log_file_p);

    createTreeFromFile(&root_p, "Tree1.txt");

    log_file_p = fopen(LOG_MD_FILE_NAME, "a");
    fprintf(log_file_p, "\n-----------------------------------------\n\n");
    fclose(log_file_p);

    bool is_continue = true;

    while(is_continue){

        printf("\nWhat do you want to do?\n"
                YELLOW "    1" DEFAULT " - save and continue guessing\n"
                YELLOW "    2" DEFAULT " - don't save and continue\n"
                YELLOW "    3" DEFAULT " - save new tree in file and exit\n"
                YELLOW "    4" DEFAULT " - don't save changes and exit\n"
                YELLOW "    5" DEFAULT " - find an object\n"
                YELLOW "    6" DEFAULT " - compare two objects\n"
                YELLOW "    7" DEFAULT " - visualize\n"
              );

        int command = getchar(); getchar();

        processCommand(command, &is_continue, root_p);
    }
}

void processCommand(int command, bool* is_continue, node_t* root_p){

    assert(is_continue);
    assert(root_p);

    switch(command){

        case '1':

            startAkinator(root_p);
            break;

        case '2':

            startAkinator(root_p);
            break;

        case '3':

            *is_continue = false;
            printTreeInFile(root_p, "Tree1.txt");
            break;

        case '4':

            *is_continue = false;
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
            *is_continue = false;
    }
}
