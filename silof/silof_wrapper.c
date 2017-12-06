//
// Created by Brendan Kristiansen on 12/4/17.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<silo.h>

DBquadmesh* get_dbquadmesh_f(char* filename, char* meshname){
    FILE* openfile = DBOpen(filename, DB_HDF5, DB_READ);
    DBquadmesh* mesh_in = DBGetQuadmesh(openfile, meshname);
    DBClose(openfile);
    return mesh_in;
}

int get_nodes_in_array(int ndims, int* dims){
    int i;
    int nodes = 0;
    for (i = 0; i < ndims; ++i){
        nodes += dims[i];
    }
    return nodes;
}

DBquadvar* get_dbquadvar_f(char* filename, char* varname){
    FILE* openfile = DBOpen(filename, DB_HDF5, DB_READ);
    DBquadvar* var_in = DBGetQuadvar(openfile, varname);
    DBClose(openfile);
    DBquadvar* corrected_var = var_in;
    corrected_var->vals = ((double*) (var_in->vals)[0]);
    return corrected_var;
}