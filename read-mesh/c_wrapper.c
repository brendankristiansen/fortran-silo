#include<stdio.h>
#include<silo.h>

typedef struct fake_mesh {
	int dimensions;		//Dimensions in mesh
	int origin;		//Origin of array
	int index_size;		//Size of start_index array
	int start_index[];	//Index of start points
}fake_mesh;

void test_mesh_(int *dimensions, int *origin, int *index_size, int*start_index){
	printf("Test mesh!\n");
	int dims = 3;
	int orig = 0;
	int size = 3;
	int index_array[] = {1, 2, 3};
	*start_index = index_array;
	*index_size = size;
	*origin = orig;
	*dimensions = dims;
}

void read_mesh_(int *dimensions, int *origin, int *index_size, int **start_index){
	printf("Reading mesh in C...\n");
	DBfile *openfile = DBOpen("sample1.silo", DB_HDF5, DB_READ);
	printf("Putting quadmesh\n");
	DBquadmesh *readmesh = DBGetQuadmesh(openfile, "testdir/mesh");
	printf("Mesh information: (C):\n");
	printf("Dimensions:\t%i\n", readmesh->dims);
	printf("Origin:\t%i\n", readmesh->origin);
	printf("index_size:\t\i\n", sizeof(readmesh->start_index));
	for(int i = 0; i < index_size; i++){
		//printf("Start index %i:\t%i\n", i, readmesh->start_index[i]);
	}
	*dimensions = readmesh->dims;
	*origin = readmesh->origin;
	*index_size = sizeof(readmesh->start_index);
	*start_index = readmesh->start_index;
}

void add_int_(int *ptr_a, int *ptr_b, int *ptr_c){
	int a = *ptr_a;
	int b = *ptr_b;
	int solution = a + b;
	*ptr_c = a + b;
	printf("C: %i + %i = %i\n", a, b, solution);
}
