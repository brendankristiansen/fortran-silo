#include <stdio.h>
#include<silo.h>

void read_mesh_(int *dimensions, int *origin, int *index_size, int *start_index){
	DBfile *openfile = DBOpen("sample.silo", DB_HDF5, DB_READ);
	DBquadmesh *readmesh = DBGetQuadmesh("sample.silo", "Mesh Silo");
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
