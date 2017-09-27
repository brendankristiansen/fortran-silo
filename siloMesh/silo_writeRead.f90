! Fortran function to write a mesh and (someday) read the mesh
program main
  ! Precision
  integer, parameter  :: SP = kind(1.0)
  integer, parameter  :: WP = kind(1.d0)

  call write_mesh
  call read_mesh

contains

  !==============!
  !  Write Mesh  !
  !==============!
  subroutine write_mesh
    implicit none
    include "silo.inc"
    integer :: dbfile,ierr,err
    integer :: ndims=3
    integer,dimension(3) :: dims=(/2,3,4/)
    real(WP), dimension(2) :: x=(/1,2/)
    real(WP), dimension(3) :: y=(/3,4,5/)
    real(WP), dimension(4) :: z=(/6,7,8,9/)


    ! Create silo database
    ierr = dbcreate("mesh.silo",9,DB_CLOBBER,DB_LOCAL,"Mesh Silo",9,DB_HDF5,dbfile)
    if (dbfile.eq.-1) then
       stop "Could not create Silo file!"
    else
       print *,'Created silo database.'
    end if

    ! Writing mesh
    err=dbputqm(dbfile,'Mesh',4,'x',1,'y',1,'z',1,real(x,SP),real(y,SP),real(z,SP),&
         dims,ndims,DB_FLOAT,DB_COLLINEAR,DB_F77NULL,ierr)

    ! Close silo database
    ierr = dbclose(dbfile)

    return
  end subroutine write_mesh

  !=============!
  !  Read Mesh  !
  !=============!
  subroutine read_mesh
    implicit none
    include "silo.inc"
    integer :: dbfile,ierr,err
    integer, parameter  :: SP = kind(1.0)
    integer, parameter  :: WP = kind(1.d0)
    integer :: ndims=3
    integer,dimension(3) :: dims=(/2,3,4/)
    real(WP), dimension(2) :: x=(/1,2/)
    real(WP), dimension(3) :: y=(/1,2,3/)
    real(WP), dimension(4) :: z=(/1,2,3,4/)

    ! ???

    return
  end subroutine read_mesh

end program main
