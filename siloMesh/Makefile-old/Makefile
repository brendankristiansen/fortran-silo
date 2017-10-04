HDF5_DIR = /usr/local/
SZIP_DIR = /usr/local/
SILO_DIR = /usr/local/
SILO_INC = -I$(SILO_DIR)/include
SILO_LIB = -L$(SILO_DIR)/lib -lsiloh5 -L$(HDF5_DIR)/lib -lhdf5 -L$(SZIP_DIR)/lib -lsz -L/usr/local/lib -lstdc++ -lz

C_SRC := $(wildcard *.c)
F_SRC := $(wildcard *.f90)
OBJECTS := $(C_SRC:%.c=%.o) $(F_SRC:%.f90=%.o)

run: silo_writeRead
	./silo_writeRead

silo_writeRead: $(OBJECTS)
	gfortran -o silo_writeRead *.o -lc $(SILO_LIB)

%.o: %.c
	gcc $(SILO_INC) -c $< -o $@

%.o: %.f90
	gfortran $(SILO_INC) -c $< -o $@ 

clean:
	rm -f *.o demo 
