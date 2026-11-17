#ifndef AKINATOR_H
#define AKINATOR_H

#include "Common.h"
#include "Tree.h"

void startAkinator(node_t* root_p);
void trainAkinator(node_t* root_p, branch_codes branch_code);

void findAnObject        (node_t* root_p);
bool checkSubtreeOnObject(node_t* root_p, const char* const object_name, size_t* const path_p, unsigned char node_depth);

return_codes getPathToTheObject(node_t* root_p, const char* const value_of_the_object, size_t* path_p);
void         compareTwoObjects (node_t* root_p);

void printObjectCharacteristic(const node_t* object_p, size_t const path, unsigned char depth);
#endif
