program driver 
    implicit none
    integer :: idims=0
    integer :: iorigin=0
    integer :: iindex=0
    integer, dimension (1) :: istart=0
    call read_mesh(idims, iorigin, iindex, istart)
    print *, "Mesh information:"
    print *, "Dimensions: ", idims
    print *, "Origin: ", iorigin
    print *, "Start index for each dimension:"
    !integer :: i 
    do iorigin = iorigin, iindex, 1
      print *, istart(iorigin)
   end do
end program
