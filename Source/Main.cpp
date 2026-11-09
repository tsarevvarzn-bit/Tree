#include "..\Headers\Main.h"

int main(){

    node_t* root_p = NULL;

    createNode(&root_p, 1);
    printTreeInConsole(root_p); putchar('\n');

    createSheet(root_p, BRANCH_LEFT, -10);
    printTreeInConsole(root_p); putchar('\n');
    // createSheet(root_p, BRANCH_RIGHT, 10);
    // printTreeInConsole(root_p); putchar('\n');
    // createSheet(root_p->right_p, BRANCH_RIGHT, 15);
    // printTreeInConsole(root_p); putchar('\n');
    // createSheet(root_p->right_p->right_p, BRANCH_RIGHT, 25);
    // printTreeInConsole(root_p); putchar('\n');
    // createSheet(root_p->right_p->right_p, BRANCH_LEFT, 13);
    // printTreeInConsole(root_p); putchar('\n');


//     createSheet(root_p->right_p, BRANCH_LEFT, 7);
//
//     createSheet(root_p->right_p->left_p, BRANCH_LEFT, 3);
//     createSheet(root_p->right_p->left_p, BRANCH_RIGHT, 8);

    visualizeTree(root_p, "labuba1.svg");

    deleteSheet(root_p, BRANCH_RIGHT);


    visualizeTree(root_p, "labuba2.svg");
}
