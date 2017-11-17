/*
 * Fortran-Silo C Wrapper
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<silo.h>

DBquadmesh* get_dbquadmesh_f();
DBquadvar* get_dbquadvar_f();

DBquadmesh* get_dbquadmesh_f(char* filename, char* varname){
	DBfile *filein = DBOpen(*filename, DB_HDF5, DB_READ);
	DBquadvar* data = DBGetQuadvar(openfile, *varname);
	DBClose(filein);
	return data;
}
