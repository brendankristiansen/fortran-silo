C_SRC := $(wildcard *.c)
F_SRC := $(wildcard *.f90)
OBJECTS := $(C_SRC:%.c=%.o) $(F_SRC:%.f90=%.o)

#export C_INCLUDE_PATH=/usr/local/include
#export LIBRARY_PATH=/usr/local/lib


run: demo
	./demo

demo: $(OBJECTS)
	gfortran -o demo *.o -lc

%.o: %.c
	#gcc -c $< -o $@
	gcc -Wall -I/usr/local/include -L/usr/local/lib *.c
	#c99 -o -I/usr/local/include -L/usr/local/lib *c demo

%.o: %.f90
	gfortran -c $< -o $@

clean:
	rm -f *.o demo

