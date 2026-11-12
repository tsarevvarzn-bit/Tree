#include "..\Headers\Main.h"

int main(){

    node_t* root_p = NULL;

//     createNode(&root_p, 1);
//
//
//     createSheet(root_p, BRANCH_LEFT, -10);
//
//     createSheet(root_p, BRANCH_RIGHT, 10);
//
//     createSheet(root_p->right_p, BRANCH_RIGHT, 15);
//
//     createSheet(root_p->right_p->right_p, BRANCH_RIGHT, 25);
//
//     createSheet(root_p->right_p->right_p, BRANCH_LEFT, 13);
//     printTreeInFile(root_p, "Tree1.txt");
//
//
//     createSheet(root_p->right_p, BRANCH_LEFT, 7);
//
//     createSheet(root_p->right_p->left_p, BRANCH_LEFT, 3);
//     createSheet(root_p->right_p->left_p, BRANCH_RIGHT, 8);
//
//     visualizeTree(root_p, "labuba1.svg");
//
//     //deleteSheet(root_p, BRANCH_RIGHT);
//
//     printTreeInFile(root_p, "Tree2.txt");
//
//     visualizeTree(root_p, "labuba2.svg");

    createTreeFromFile(&root_p, "Tree1.txt");


    visualizeTree(root_p, "labuba3.svg");

}
