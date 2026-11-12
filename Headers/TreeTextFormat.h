#ifndef TREETEXTFORMAT_H
#define TREETEXTFORMAT_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "Common.h"
#include "Tree.h"

return_codes printTreeInFile      (const node_t* const root_p, const char* const name_of_out_file);
void         printSubtreeInFile   (const node_t* const root_p, FILE* const out_file_p);

return_codes createTreeFromFile   (node_t** const root_p_p, const char* const name_of_in_file);
return_codes createSubtreeFromFile(node_t*  const parent_p, const char* const tree_text, size_t* const symbol_idx_p);

return_codes processBrunch        (node_t*  const parent_p, const char* const tree_text, size_t* const symbol_idx_p, const branch_codes branch_code);
return_codes startProcessingFile  (node_t** const root_p_p, const char* const tree_text);

#endif
