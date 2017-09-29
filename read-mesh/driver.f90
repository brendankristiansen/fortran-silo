program driver
    print *, "Reading silo mesh..."
    integer :: dimensions,origin,index_size,start_index
    call read_mesh(dimensions, origin, start_index)
    print *, "Mesh information:"
    print *, "Dimensions: ", dimensions
    print *, "Origin: ", origin
    print *, "Start index for each dimension:"
    do i = origin, index_size
      print *, start_index (i)
   end do
end program
