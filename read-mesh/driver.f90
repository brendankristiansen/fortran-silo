program driver 
    implicit none
    integer :: idims=0
    integer :: iorigin=0
    integer :: iindex=0
    integer, dimension (3) :: istart=0
    call test_mesh(idims, iorigin, iindex, istart)
    print *, "Mesh Information!!"
    print *, "Dimensions:", idims
    print *, "Origin:", iorigin
    print *, "Index size:", iindex
    print *, "Start index for each dimension:"
    do iorigin = iorigin, iindex, 1
        print *, istart(iorigin)
        end do
    call read_mesh(idims, iorigin, iindex, istart)
    print *, "Mesh information (Fortran):"
    print *, "Dimensions: ", idims
    print *, "Origin: ", iorigin
    print *, "Start index for each dimension:"
    !integer :: i 
    do iorigin = iorigin, iindex, 1
      print *, istart(iorigin)
      end do
end program
