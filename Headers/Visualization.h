#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "Common.h"

const int MAX_LEN_OF_STR_FOR_SYSTEM_CALL = 250;
const int SYSTEM_CORRECT_RETURN          =   0;

void visualizeTree             (const node_t* const root_p, const char * const name_of_file);
void addTreeToVisualization    (const node_t* const root_p, FILE* const out_file_p);


#endif
