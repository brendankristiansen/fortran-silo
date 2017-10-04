#include<stdio.h>
#include<silo.h>

void read_mesh_(int *dimensions, int *origin, int *index_size, int **start_index){
	printf("Reading mesh in C...\n");
	DBfile *openfile = DBOpen("sample1.silo", DB_HDF5, DB_READ);
	printf("Putting quadmesh");
	DBquadmesh *readmesh = DBGetQuadmesh(openfile, "testdir/mesh");
	printf("read dim[0] is %d\n", readmesh->dims[0]);
	//*dimensions = readmesh->dims;
	//*origin = readmesh->origin;
	//*index_size = sizeof(readmesh->start_index);
	*start_index = readmesh->start_index;
}

void add_int_(int *ptr_a, int *ptr_b, int *ptr_c){
	int a = *ptr_a;
	int b = *ptr_b;
	int solution = a + b;
	*ptr_c = a + b;
	printf("C: %i + %i = %i\n", a, b, solution);
}
