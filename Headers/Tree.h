#ifndef TREE_H
#define TREE_H


#include "Common.h"

return_codes createNode        (node_t** const root_p_p, int value);
return_codes createSheet       (node_t* const parent_p, branch_codes branch_code, int value);

return_codes deleteNode        (node_t* const node_p);
return_codes deleteSheet       (node_t* const parent_p, branch_codes branch_code);

void         printTreeInConsole(const node_t* const root_p);


#endif
