# GPU_3D_CDT_Refine
A 3D CDT Refinement Software on GPU

Project Website: https://www.comp.nus.edu.sg/~tants/gqm3d.html

Paper: Computing Three-dimensional constrained Delaunay Refinement Using the GPU. Z. Chen and T.S. Tan. The 28th International Conference on Parallel Architectures and Compilation Techniques, 21-25 September, 2019, Seattle, WA, USA. (<a href="#">PDF</a>)

* A NVIDIA GPU is required since this project is implemented using CUDA.
* The development environment: Visual Studio 2017 and CUDA 9.0. (Need to include both CUDA SDK and Sample. The later is for timing routines. Changes for paths might be needed for Visual Studio project setting. Please use x64 and Release mode.)
* TetGen 1.5 is used. Check http://wias-berlin.de/software/index.jsp?id=TetGen&lang=1 for more information.
* CGAL 4.13 is used for comparision. Check https://www.cgal.org/index.html for more information. You might remove Experiment_CGAL.h and Experiment_CGAL.cpp if you don't want to use CGAL.

--------------------------------------------------------------
GPU Refinement Routine (located in MeshRefine.h and MeshRefine.cpp):  
void <b>refineInputFileOnGPU</b>(  
&nbsp;&nbsp;&nbsp;&nbsp; char* infile,  
&nbsp;&nbsp;&nbsp;&nbsp; int format,  
&nbsp;&nbsp;&nbsp;&nbsp; MESHBH* input_behavior,  
&nbsp;&nbsp;&nbsp;&nbsp; char* outmesh,  
&nbsp;&nbsp;&nbsp;&nbsp; char* outdata)

This routine calls both TetGen (tetgen.h and tetgen.cpp) and the GPU refinement pipeline <b>GPU_Refine_3D</b> (CudaRefine.h and CudaRefine.cu) to refine the input mesh, and output the quality mesh and its statistic.

char* infile:  
The path for input mesh.

int format:  
* 0: Load the input mesh from <a href="http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_node">.node</a> and <a href="http://wias-berlin.de/software/tetgen/1.5/doc/manual/manual006.html#ff_poly">.poly</a> files.
* 1: Load the input mesh from <a href="https://en.wikipedia.org/wiki/OFF_(file_format)">.off</a> file.

MESHBH* input_behavior:  
* double radius_to_edge_ratio:  
The upper bound for the radius-edge ratio of tetrahedron. The default value is 1.6.

* int minsplittabletets:  
The number of splittable bad tetrahedra allowed in the output mesh. The routine will stop when the number of splittable bad tettrahedra is less than or equal to minsplittabletets. The default value is 0, which means no splittable bad tet is allowed.

* int minbadtets:  
The number of bad tetrahedra allowed in the output mesh. The routine will stop when the number of bad tettrahedra is less than or equal to minbadtets. The default value is 0, which means no bad tet is allowed.

* int miniter:  
The number of total iteration allowed. The routine will stop when the number of iterations is greater than or equal to miniter, and when the number of points to be inserted is smaller than minthread. The default value is 0, which means no restriction for the iteration number.

* int minthread:  
The lower bound for the number of points to be inserted in one iteration. When the iteration number is greater than or equal to miniter, the routine verifies in every iteration whether the number of points to be inserted is less than minthread. If so, the routine terminates immediately due to low concurrency. This is designed for the case where the over-refinement causes the long-tail with small number of threads and thus the waste of time. The default value is 0, which means the routine would not terminate when the concurrency is low.

* int maxcavity:  
The upper bound for the number of tetrahedra in the cavity of point of an element. Such an element would be marked as unsplittable if its cavity size exceeds maxcavity, and its corresponding point is rejected. The default value is 500.

* int mode:  
Two available modes: gQM3D (mode = 1) and gQM3D+ (mode = 2). In gQM3D, TetGen computes the CDT of the input PLC first, and then passes the CDT to the GPU_Refine_3D routine; while in gQM3D+, TetGen first computes the CDT of the input PLC, then splits all encroached subsegment and subfaces, and then passes the intermidate mesh to the GPU_Refine_3D routine.

* internalmesh* drawmesh:  
For debug only. If drawmesh is not NULL, the intermidate mesh would be stored in this structure.
	
char* outmesh:  
The path for output mesh.

char* outdata:  
The path for output mesh statistic. This includes the final element numbers, timing for different stages, and the dihedral angle distribution.

--------------------------------------------------------------
Experiment

All experiments were conducted on a PC with an Intel i7-7700k 4.2GHz CPU, 32GB of DDR4 RAM and a GTX1080 Ti graphics card with 11GB of video memory.




--------------------------------------------------------------

Proceed to main.cpp to check how to call gpu and cpu refinement routines properly.

