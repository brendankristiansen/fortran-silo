#include <stdio.h>
#include<silo.h>

//int main(void){
//	printf("C Wrapper!\n");
//	return 0;
//}

void to_int_(int *int_ptr) {
    int i = *int_ptr;
    printf("i in c = %d\n", i);
}

void add_int_(int *ptr_a, int *ptr_b, int *ptr_c){
	int a = *ptr_a;
	int b = *ptr_b;
	int solution = a + b;
	*ptr_c = a + b;
	printf("C: %i + %i = %i\n", a, b, solution);
}

void silo_test_(){
	DBfile *file = DBCreate("sample.silo", DB_CLOBBER, DB_LOCAL, NULL, DB_HDF5);
	printf("File opened!\n");
	DBClose(file);
}
