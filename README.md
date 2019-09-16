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


char* outmesh:


char* outdata:  

--------------------------------------------------------------
Experiment



--------------------------------------------------------------

Proceed to main.cpp to check how to call gpu and cpu refinement routines properly.

