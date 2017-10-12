#include<stdio.h>
#include<stdlib.h>
#include<silo.h>

typedef struct fake_mesh {
	int dimensions;		//Dimensions in mesh
	int origin;		//Origin of array
	int index_size;		//Size of start_index array
	int start_index[];	//Index of start points
}fake_mesh;

typedef struct {
	int len;
	int *content; 
} c_int_array;

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

//int* test_mesh_(int *dimensions, int *origin, int *index_size ){
void test_mesh(c_int_array *my_array){
	//int dims = 3;
	//int orig = 0;
	int size = 3;

	c_int_array *x = create_c_array(size);
	printf("len: %d\n", x->len);
	*my_array = *x;
	printf("len: %d\n", (my_array)->len);
	//*index_size = size;
	//*origin = orig;
	//*dimensions = dims;
	//return start_index;
}

//void read_mesh_(int *dimensions, int *origin, int *index_size, int **start_index){
//	printf("Reading mesh in C...\n");
//	DBfile *openfile = DBOpen("sample1.silo", DB_HDF5, DB_READ);
//	printf("Putting quadmesh\n");
//	DBquadmesh *readmesh = DBGetQuadmesh(openfile, "testdir/mesh");
//	printf("Mesh information: (C):\n");
//	printf("Dimensions:\t%i\n", readmesh->dims);
//	printf("Origin:\t%i\n", readmesh->origin);
//	printf("index_size:\t\i\n", sizeof(readmesh->start_index));
//	for(int i = 0; i < index_size; i++){
//		//printf("Start index %i:\t%i\n", i, readmesh->start_index[i]);
//	}
//	*dimensions = readmesh->dims;
//	*origin = readmesh->origin;
//	*index_size = sizeof(readmesh->start_index);
//	*start_index = readmesh->start_index;
//}

void add_int_(int *ptr_a, int *ptr_b, int *ptr_c){
	int a = *ptr_a;
	int b = *ptr_b;
	int solution = a + b;
	*ptr_c = a + b;
	printf("C: %i + %i = %i\n", a, b, solution);
}
