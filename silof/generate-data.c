//
// Created by Brendan Kristiansen on 12/4/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <silo.h>
#include "silof_wrapper.h"

const char* FILENAME = "silo-sample.silo";
const char* MESHNAME = "samplemesh";
const char* VARNAME = "samplevar";

const bool GENERATE_MESH = TRUE;
const bool GENERATE_VAR = TRUE;

int main(void){
    DBfile *file = DBCreate(FILENAME, DB_CLOBBER, DB_LOCAL, NULL, DB_HDF5);
    if (file == NULL) {
        printf("ERROR!");
        return -1;
    }

    int ndims = 3;
    int dims[ndims] = {2, 3, 4};
    double data[2][3][4];
    int i, j, k;

    int nodes = 0;
    for(i = 0; i < ndims; ++i){
        nodes += dims[i];
    }

    if(GENERATE_MESH == TRUE) {

        char *coordnames[3];

        coordnames[0] = strdup("x");
        coordnames[1] = strdup("y");
        coordnames[2] = strdup("z");
        double* coordinates = (double*) malloc(sizeof(double) * nodes);

        double cell = 1.0;
        for (i = 0; i < nodes; ++i) {
            coordinates[i] = cell;
            cell += 1.0;
        }

        DBPutQuadmesh(file, MESHNAME, coordnames, coordinates, dims, 2, DB_DOUBLE, DB_COLLINEAR, NULL);
    }

    if(GENERATE_VAR == TRUE){
        double cell = 1.0;
        for (i = 0; i < dims[0]; ++i) {
            for (j = 0; j < dims[1]; ++j) {
                for (k = 0; k < dims[2]; ++k) {
                    data[i][j][k] = cell;
                    cell += 1.0;
                }
            }
        }

        int dims[3] = {2, 3, 4};

        DBPutQuadvar1(file, VARNAME, MESHNAME, data, dims, 3, NULL, 0, DB_DOUBLE, DB_ZONECENT, NULL);
    }

    DBClose(file);
}