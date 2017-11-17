type, bind(c) :: dbquadmesh
	implicit none
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

type, bind(c) :: dbquadvar
end type

interface
        integer(c_size_t) function strlen(str) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_size_t
            !implicit none
            type(c_ptr), intent(in), value :: str
        end function
    end interface

subroutine get_dbquadmesh_f()
	use iso_c_binding
	implicit none	
end subroutine
