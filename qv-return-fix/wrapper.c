#include <stdio.h>
#include <stdlib.h>
#include <silo.h>
#include <string.h>

/*
 * Array of integers with length
 */
typedef struct {
    int len;
    int *content;
} c_int_array;

/*
 * Array of doubles with length
 */
typedef struct {
    int len;
    double *content;
} c_double_array;

/*
 * Quadmesh data struct
 * Contains:
 *      Number of dimensions
 *      Length of each dimension
 *      Number of nodes
 *      1-dimensional double array containing mesh values
 */
typedef struct {
    int ndims;
    int* dims;
    int nodes;
    double* data;
} quadmesh_data;

/*
 * constants for filename and mesh name
 */
const char* MESH_NAME = "mesh_name";
const char* FILENAME = "sample.silo";

/*
 * Creates sample.silo with basic test mesh
 */
void create_silo_file_(void) {
    DBfile *file = DBCreate(FILENAME, DB_CLOBBER, DB_LOCAL, NULL, DB_HDF5);
    if (file == NULL) {
        printf("ERROR!");
        return;
    }

    char* coordnames[3];
    double nodex[2] = {1.0, 2.0};
    double nodey[3] = {3.0, 4.0, 5.0};
    double nodez[4] = {6.0, 7.0, 8.0, 9.0};
    int dimensions[3] = {2, 3, 4};

    coordnames[0] = strdup("x");
    coordnames[1] = strdup("y");
    coordnames[2] = strdup("z");

    double *coordinates[3] = {nodex, nodey, nodez};

    DBPutQuadmesh(file, MESH_NAME, coordnames, coordinates, dimensions, 2, DB_DOUBLE, DB_COLLINEAR, NULL);

    double data[2][3][4];
    int i, j, k;
    double cell = 1.0;
    for(i = 0; i < 2; ++i){
        for(j = 0; j < 3; ++j){
            for (k = 0; k < 4; ++k){
                data[i][j][k] = cell;
                cell += 1.0;
            }
        }
    }

    int dims[3] = {2, 3, 4};

    DBPutQuadvar1(file, "data", MESH_NAME, data, dims, 3, NULL, 0, DB_DOUBLE, DB_ZONECENT, NULL);

    DBClose(file);
}

/*
 * Generates C int array
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
DBquadmesh* load_dbquadmesh(){
    DBfile *openfile = DBOpen(FILENAME, DB_HDF5, DB_READ);
    DBquadmesh *readmesh = DBGetQuadmesh(openfile, MESH_NAME);
    //DBClose(openfile);
    printf("Mesh coords in C: %f\n", ((double**)(readmesh->coords))[0][0]);
    // BRENDAN-- print out the contents of readmesh->coords
    return readmesh;
}

c_int_array* load_quadvar_size(){
    DBfile *openfile = DBOpen(FILENAME, DB_HDF5, DB_READ);
    DBquadvar* data = DBGetQuadvar(openfile, "data");
    DBClose(openfile);

    double*** array = ((double***)data->vals);
    return array;
}

int* get_elements(int dimension){
    DBfile *openfile = DBOpen(FILENAME, DB_HDF5, DB_READ);
    DBquadvar* data = DBGetQuadvar(openfile, "data");
    DBClose(openfile);
    return ((int*)(data->dims)[dimension]);
}

/*
 * Returns number of data points in a mesh
 */
int get_linear_array_size(int ndims, int* dims){
    int i, size = 1;
    for (i = 0; i < ndims; ++i) {
        size *= dims[i];
    }
    return size;
}

/*
 * Corrects weird array pointer issue.
 * Returns pointer to 1-dimensional array of data
 * TODO: pass filename, mesh name, and data variable name as arguments if F90 allows easily
 */
quadmesh_data* get_linear_array(){
    DBfile *openfile = DBOpen(FILENAME, DB_HDF5, DB_READ);
    DBquadvar* data = DBGetQuadvar(openfile, "data");
    DBClose(openfile);
    int array_size = get_linear_array_size(data->ndims, data->dims);
    int i;
    quadmesh_data* corrected_mesh;
    corrected_mesh = (quadmesh_data*) malloc(sizeof(quadmesh_data));
    corrected_mesh->ndims = data->ndims;
//    for(i = 0; i < corrected_mesh->ndims; ++i){
//        corrected_mesh->dims[i] = data->dims[i];
//    }
    corrected_mesh->dims = (data->dims);
    corrected_mesh->data = ((double*) (data->vals)[0]);
//    for (i = 0; i < array_size; i++) {
//        corrected_mesh->data[i] = ((double **) (data->vals))[0][i];
//    }
    corrected_mesh->nodes = array_size;
    return corrected_mesh;
    //(*val) = ((double**)(data->vals))[0][*x];
}

void get_linear_array_sub(quadmesh_data* data) {
    quadmesh_data *tmp = get_linear_array();
    *data = *tmp;
}