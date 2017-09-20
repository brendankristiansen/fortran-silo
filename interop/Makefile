C_SRC := $(wildcard *.c)
F_SRC := $(wildcard *.f90)
OBJECTS := $(C_SRC:%.c=%.o) $(F_SRC:%.f90=%.o)

run: demo
	./demo

demo: $(OBJECTS)
	gfortran -o demo *.o -lc

%.o: %.c
	gcc -c $< -o $@

%.o: %.f90
	gfortran -c $< -o $@

clean:
	rm -f *.o demo

