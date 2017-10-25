This folder contains example silo files writen from the NGA code.  

Each file has a 3D mesh called Mesh that is with extents:
x = -0.5:0.5          with 32 grid cells
y = 0:1               with 32 grid cells
z = -0.015625:0.15625 with  1 grid cell (this makes it practically 2D, but all runs output 3D data)

The files contain one variable call fun defined with
  fun=sin(2*pi*x)*cos(2*pi*y) 
and is shown in the image data.png

Files created with different numbers of processors and groups are provided.
 
