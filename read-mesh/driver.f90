program driver 
    use iso_c_binding
    implicit none

    type, bind(C) :: c_int_array
            integer(C_INT) :: len
            type(c_ptr) :: content
    end type 

    interface 
            subroutine test_mesh(my_array) bind(c)
                    implicit none
                    import :: c_int_array
                    type(c_int_array) :: my_array
            end subroutine
    end interface

    type, bind(C) :: db_quadmesh
           implicit none
           integer(C_INT) :: id                                         ! Identifier for this object
           integer(C_INT) :: block_no                                   ! Block number for this mesh
           integer(C_INT) :: group_no                                   ! Block group number for this mesh
           type(C_PTR) :: mesh_name                                     ! Name associated with mesh
           integer(C_INT) :: cycle_num                                  ! Problem cycle number
           integer(C_INT) :: coord_sys                                  ! Cartesian, cylindrical, spherical
           integer(C_INT) :: major_order                                ! 1 indicates row-major for multi-dimensional arrays
           integer(C_INT), pointer :: stride                            ! Offsets ti adjacent elements
           integer(C_INT) :: coordtype                                  ! Coordinates array type: collinear, non-collinear
           integer(C_INT) :: facetype                                   ! Zone face type: rect, curv
           integer(C_INT) :: planar                                     ! Sentinel: zones represent area or volume
           ! C data type is void. Problem??
           type(c_ptr) :: coords                                        ! Mesh node coordinate pointers [ndims]
           
           integer(C_INT) :: datatype                                   ! Type of coordinate arrays (double, float)
           real(C_FLOAT) :: time                                        ! Problem time
           real(C_DOUBLE) :: dtime                                      ! Problem time, double data type (Unnecessary??)
           real(C_FLOAT), pointer :: min_extents                        ! Minimum mesh extents
           real(C_FLOAT), pointer :: max_extents                        ! Maximum mesh extents
           type(C_PTR) :: labels                                        ! Label associated with each dimension
           type(C_PTR) :: units                                         ! Units for variable
           integer(C_INT) :: ndims                                      ! Number of computational dimensions
           integer(C_INT) :: nspace                                     ! Number of physical dimensions
           integer(C_INT) :: nnodes                                     ! Total number of nodes
           integer(C_INT), pointer :: dims                              ! Number of nodes per dimension
           integer(C_INT) :: origin                                     ! 0 or 1
           integer(C_INT), pointer :: min_index                         ! Index in each dimension of 1st non-phoney
           integer(C_INT), pointer :: max_index                         ! Index in each dimension of last non-phoney
           integer(C_INT), pointer :: base_index                        ! Lowest real i, j, k value for this block
           integer(C_INT), pointer :: start_index                       ! i, j, k values corresponding to original mesh
           integer(C_INT), pointer :: size_index                        ! Number of nodes per diumension for original mes
           integer(C_INT) :: guihide                                    ! Flag to hide from post-processor's GUI
           type(C_PTR) :: mrgtree_name                                  ! Optional name of assoc. mrgtree object
           type(C_PTR) :: ghost_name_labels
    end type

    interface
            subroutine load_dbquadmesh(quadmesh) bind(c)
                    import :: db_quadmesh
                    type(db_quadmesh) :: quadmesh
            end subroutine
    end interface

    ! integer :: idims=0
    ! integer :: iorigin=0
    ! integer :: iter=0
    ! integer :: iindex=0
    type(C_PTR) :: istart
    integer(C_INT), pointer :: pa(:) => null()
    type(c_int_array) :: my_array

    print *, "#####################"
    print *, "# C GENERATED ARRAY #"
    print *, ""
    call test_mesh(my_array)
    print *, "Mesh Information!!"
    !print *, "Dimensions:", idims
    ! print *, "Origin:", iorigin
    ! print *, "Index size:", iindex
        
    print *, "my_array:", my_array%len
    call c_f_pointer(my_array%content, pa, shape=[my_array%len])
    print *, "my_content:", pa 

    call read_mesh(idims, iorigin, iindex, istart)
    print *, "Mesh information (Fortran):"
    print *, "Dimensions: ", idims
    print *, "Origin: ", iorigin
    print *, "Start index for each dimension:", istart
    print *, ""
    print *, "###################"
    print *, "# READ DBQUADMESH #"
    print *, ""
    type(db_quadmesh) :: quadmesh_in
    character(C_CHAR) (len=256), pointer :: mesh_name(:) => null()
    call load_dbquadmesh(quadmesh_in)
    call c_f_pointer(quadmesh_in%mesh_name, mesh_name, shape=[256])
    print *, "Mesh name: "
end program
