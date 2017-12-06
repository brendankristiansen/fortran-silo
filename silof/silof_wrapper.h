//
// Created by Brendan Kristiansen on 12/4/17.
//

#include <silo.h>

#ifndef SILOF_SILOF_WRAPPER_H
#define SILOF_SILOF_WRAPPER_H

#endif //SILOF_SILOF_WRAPPER_H

DBquadmesh* get_dbquadmesh_f(char* filename, char* varname);
int get_nodes_in_array(int ndims, int* dims);
DBquadvar get_dbquadvar_f(char* filename, char* varname);