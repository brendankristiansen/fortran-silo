module silof
    implicit none
    use iso_c_binding

    ! Silo DB_Quadmesh Type
    type, bind(C) :: db_quadmesh
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

    ! Silo DB_Quadvar Type
    type, bind(c) :: db_quadvar
        integer(C_INT) :: id                                        ! Identifier for this object
        type(C_PTR) :: name                                         ! Name of variable
        type(C_PTR) :: units                                        ! Units for variable
        type(C_PTR) :: label                                        ! Label
        integer(C_INT) :: cycle                                     ! Problem Cycle Number
        type(C_PTR) :: vals                                         ! Array of pointers to data arrays
        integer(C_INT) :: datatype                                  ! Type of data pointed to by 'vals'
        integer :: nels                                             ! Number of elements in each array
        integer :: nvals                                            ! Number of arrays pointed to by 'vals'
        integer :: ndims                                            ! Rank of variable
        integer(C_INT), pointer :: dims                             ! Number of elements in each dimension
        integer(C_INT) :: major_order                               ! 1 indicates row-major for multi-d arrays
        integer(C_INT), pointer :: stride                           ! Offsets to adjacent elements
        integer(C_INT), pointer :: min_index                        ! Index in each dimension of 1st non-phoney
        integer(C_INT), pointer :: max_index                        ! Index in each dimension of last non-phoney
        integer(C_INT) :: origin                                    ! 0 or 1
        real(C_FLOAT) :: time                                       ! Problem time
        real(C_DOUBLE) :: dtime                                     ! Problem time, double data type
        real(C_FLOAT), pointer :: align                             ! Centering and alignment per dimension
        type(C_PTR) :: mixvals                                      ! nvals ptrs to data arrays for mixed zones
        integer(C_INT) :: mixlen                                    ! Number of elements in each mixed zone array
        integer(C_INT) :: use_specmf                                ! Flag indicating whether to apply species mass
                                                                        ! fractions to the variable
        integer(C_INT) :: ascii_labels                              ! Treat variable values as ASCII values by rounding
                                                                        ! to the nearest integer in the range [0, 255]
        type(C_PTR) :: meshname                                     ! Name of associated mesh
        integer(C_INT) :: guihide                                   ! Flag to hide from post-processor's GUI
        integer(C_INT) :: conserved                                 ! Indicates if the variable should be conserved
                                                                        ! under various operations such as interp
        integer(C_INT) :: extensive                                 ! Indicates if the variable represents an extensive
                                                                        ! physical property
        integer(C_INT) :: centering                                 ! Explicit centering knowledge
        real(C_DOUBLE) :: missing_value                             ! value to indicate var data is invalid/missing
    end type db_quadvar
end module silof