! #############################
! Driver for fortran-silo test.
! #############################
program silo_readwrite
    use iso_c_binding
    implicit none

    ! ###########################################
    ! DBquadmesh Struct converted to fortran type
    ! ###########################################
    type, bind(C) :: db_quadmesh
        !implicit none
        integer(C_INT) :: id                                         ! Identifier for this object
        integer(C_INT) :: block_no                                   ! Block number for this mesh
        integer(C_INT) :: group_no                                   ! Block group number for this mesh
        type(C_PTR) :: mesh_name                                     ! Name associated with mesh
        integer(C_INT) :: cycle_num                                  ! Problem cycle number
        integer(C_INT) :: coord_sys                                  ! Cartesian, cylindrical, spherical
        integer(C_INT) :: major_order                                ! 1 indicates row-major for multi-dimensional arrays
        type(C_PTR):: stride                                         ! Offsets ti adjacent elements
        integer(C_INT) :: coordtype                                  ! Coordinates array type: collinear, non-collinear
        integer(C_INT) :: facetype                                   ! Zone face type: rect, curv
        integer(C_INT) :: planar                                     ! Sentinel: zones represent area or volume
        ! C data type is void. Problem??
        type(c_ptr) :: coords                                        ! Mesh node coordinate pointers [ndims]
        integer(C_INT) :: datatype                                   ! Type of coordinate arrays (double, float)
        real(C_FLOAT) :: time                                        ! Problem time
        real(C_DOUBLE) :: dtime                                      ! Problem time, double data type (Unnecessary??)
        type(C_PTR) :: min_extents                                   ! Minimum mesh extents
        type(C_PTR) :: max_extents                                   ! Maximum mesh extents
        type(C_PTR) :: labels                                        ! Label associated with each dimension
        type(C_PTR) :: units                                         ! Units for variable
        integer(C_INT) :: ndims                                      ! Number of computational dimensions
        integer(C_INT) :: nspace                                     ! Number of physical dimensions
        integer(C_INT) :: nnodes                                     ! Total number of nodes
        type(C_PTR) :: dims                                          ! Number of nodes per dimension
        integer(C_INT) :: origin                                     ! 0 or 1
        type(C_PTR) :: min_index                                     ! Index in each dimension of 1st non-phoney
        type(C_PTR) :: max_index                                     ! Index in each dimension of last non-phoney
        type(C_PTR) :: base_index                                    ! Lowest real i, j, k value for this block
        type(C_PTR) :: start_index                                   ! i, j, k values corresponding to original mesh
        type(C_PTR) :: size_index                                    ! Number of nodes per diumension for original mes
        type(C_PTR) :: guihide                                       ! Flag to hide from post-processor's GUI
        type(C_PTR) :: mrgtree_name                                  ! Optional name of assoc. mrgtree object
        type(C_PTR) :: ghost_name_labels
    end type

    ! ##############################
    ! Interface for loading quadmesh
    ! ##############################
    interface
        subroutine load_dbquadmesh(quadmesh) bind(c)
            import :: db_quadmesh
            type(db_quadmesh) :: quadmesh
        end subroutine
    end interface

    ! ################
    ! C int array type
    ! ################
    type, bind(C) :: c_int_array
        integer(C_INT) :: len                                       ! Length of array
        type(c_ptr) :: content                                      ! Contents of int array
    end type

    ! #########################
    ! Interface for C int array
    ! #########################
    interface
        subroutine test_mesh(my_array) bind(c)
            import :: c_int_array
            type(c_int_array) :: my_array
        end subroutine
    end interface

    ! ################
    ! C int array data
    ! ################
    type(c_int_array) :: my_array
    integer(C_INT), pointer :: pa(:) => null()

    ! #########
    ! Mesh Data
    ! #########
    type(db_quadmesh) :: quadmesh_in
    character, pointer :: mesh_name(:) => null()
    integer, pointer :: stride(:) => null()
    integer, pointer :: coords(:) => null()
    real, pointer :: min_extents(:) => null()
    real, pointer :: max_extents(:) => null()
    integer, pointer :: dims(:) => null()
    integer, pointer :: min_index(:) => null()
    integer, pointer :: max_index(:) => null()
    integer, pointer :: base_index(:) => null()
    integer, pointer :: start_index(:) => null()
    integer, pointer :: size_index(:) => null()

    ! #####
    ! Begin
    ! #####

    ! Create test data
    print *, "#####################"
    print *, "# C GENERATED ARRAY #"
    print *, ""
    call test_Array(my_array)
    print *, "Test array: (should be 123)"

    print *, "Array length:", my_array%len
    call c_f_pointer(my_array%content, pa, shape=[my_array%len])
    print *, "Contains:", pa
    print *, "FINISHED WITH C ARRAY"
    print *, "#####################"

    ! Create silo file
    print *, "######################"
    print *, "# CREATING SILO FILE #"
    print *, ""
    call create_silo_file()
    print *, "FINISHED CREATING SILO FILE"
    print *, "######################"

    ! Read silo file
    print *, "###################"
    print *, "# READ DBQUADMESH #"
    print *, ""
    call load_dbquadmesh(quadmesh_in)
    call c_f_pointer(quadmesh_in%mesh_name, mesh_name, shape=[4])   ! Big ol' problem here: need to know length of arrays
    call c_f_pointer(quadmesh_in%coords, coords, shape=[30])        ! Other problem: coords is 2-dimensional
    print *, "Mesh name: ", mesh_name
    print *, "Mesh origin: ", quadmesh_in%origin
    print *, "Coordinates: ", coords
    print *, "FINISHED READING MESH"
    print *, "###################"
end program