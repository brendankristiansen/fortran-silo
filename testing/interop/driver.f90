program driver
    integer :: i=7
    integer :: a=5
    integer :: b=10
    integer :: c=0
    print *, "i in fortran = ",i
    call to_int(i)
    call add_int(a, b, c)
    print *, a, " + ", b, " = ", c
    print *, "Silo test: "
    call silo_test()
end program
