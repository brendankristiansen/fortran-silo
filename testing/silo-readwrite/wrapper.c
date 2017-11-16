#include <stdio.h>
#include <stdlib.h>
#include <silo.h>
#include <string.h>

typedef struct {
    int len;
    int *content;
} c_int_array;

const char* MESH_NAME = "mesh_name";

/*
 * Creates sample.silo with basic test mesh
 */
void create_silo_file_(void) {
    DBfile *file = DBCreate("sample.silo", DB_CLOBBER, DB_LOCAL, NULL, DB_HDF5);
    if (file == NULL) {
        printf("ERROR!");
        return;
    }

    char *coordnames[3];
    double nodex[2] = {1.0, 2.0};
    double nodey[3] = {3.0, 4.0, 5.0};
    double nodez[4] = {6.0, 7.0, 8.0, 9.0};
    int dimensions[3] = {2, 3, 4};

    coordnames[0] = strdup("x");
    coordnames[1] = strdup("y");
    coordnames[2] = strdup("z");

    double *coordinates[3] = {nodex, nodey, nodez};
    DBPutQuadmesh(file, MESH_NAME, NULL, coordinates, dimensions, 3, DB_FLOAT, DB_COLLINEAR, NULL);

    DBClose(file);
}

/*
 * Generates C array
 */
c_int_array* create_c_array(int n) {
    c_int_array* this;
    int i;
    this = (c_int_array*) malloc(sizeof(c_int_array));
    this->len = n;
    this->content = (int*)malloc(sizeof(int)*n);
    for (i = 0 ; i < n ; i++) {
        this->content[i] = i+1;
    }
    return this;
}

/*
 * Generates a test array. Returns to fortran
 */
void test_array_(c_int_array *my_array){
    int size = 3;
    c_int_array *x = create_c_array(size);
    *my_array = *x;
    printf("len: %d\n", (my_array)->len);
}

/*
 * Opens sample.silo. Returns quadmesh to Fortran
 */
DBquadmesh load_dbquadmesh(){
    DBfile *openfile = DBOpen("sample.silo", DB_HDF5, DB_READ);
    DBquadmesh *readmesh = DBGetQuadmesh(openfile, MESH_NAME);
    DBClose(openfile);
    int i;
    for(i = 0; i < sizeof(readmesh->coords); ++i){
	printf("Mesh coords in C: %d\n", readmesh->coords[i]);
    }
    // BRENDAN-- print out the contents of readmesh->coords
    return *readmesh;
}
