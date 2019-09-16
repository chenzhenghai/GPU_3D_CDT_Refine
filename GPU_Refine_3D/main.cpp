#include "InputGenerator.h"
#include "tetgen.h"
#include "Experiment.h"
#include "Experiment_CGAL.h"
#include "MeshChecker.h"
#include "Viewer.h"
#include "CudaRefine.h"
#include "MeshRefine.h"

/**
* Host main routine
*/
int
main(int argc, char** argv)
{
	//CGAL
	//refineMeshCPU_CGAL_without_acute_angles();
	
	//TetGen
	//refineInputFileOnCPU(
	//	"input_real/Done/Sculpture01",
	//	1,
	//	1.4,
	//	"input_real/Sculpture01_cpu_1.4.mesh",
	//	"input_real/Sculpture01_cpu_1.4.txt"
	//);

	MESHBH behavior;
	behavior.radius_to_edge_ratio = 1.4;
	behavior.minsplittabletets = 0;
	behavior.minbadtets = 1960000;
	behavior.miniter = 0;
	behavior.minthread = 0;
	behavior.maxcavity = 500;
	behavior.mode = 2;
	behavior.drawmesh = NULL;

	refineInputFileOnGPU(
		"input_real/Sculpture01",
		1,
		&behavior,
		"Sculpture01_gpu_star_1.4.mesh",
		"Sculpture01_gpu_star_1.4.txt"
	);

	return 0;
}