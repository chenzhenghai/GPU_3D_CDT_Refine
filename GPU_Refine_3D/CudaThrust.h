#pragma once

#include <thrust/device_ptr.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/sequence.h>
#include <thrust/unique.h>
#include <thrust/count.h>
#include <thrust/inner_product.h>
#include <thrust/transform.h>
#include <thrust/extrema.h>
#include "MeshStructure.h"

#define REAL double
#define REAL2 double2
#define REAL3 double3
#define BYTE char
#define uint64	unsigned long long

// Thrust
typedef thrust::device_ptr<int> IntDPtr;
typedef thrust::device_ptr<char> ByteDPtr;
typedef thrust::device_ptr<unsigned long> ULongDPtr;
typedef thrust::device_ptr<unsigned long long> UInt64DPtr;
typedef thrust::device_ptr<int2> Int2DPtr;
typedef thrust::device_ptr<REAL2> Real2DPtr;
typedef thrust::device_ptr<REAL3> Real3DPtr;

typedef thrust::device_vector<int> IntD;
typedef thrust::device_vector<unsigned int> UIntD;
typedef thrust::device_vector<int2> Int2D;
typedef thrust::device_vector<BYTE> ByteD;
typedef thrust::device_vector<unsigned long> ULongD;
typedef thrust::device_vector<unsigned long long> UInt64D;
typedef thrust::device_vector<REAL> RealD;
typedef thrust::device_vector<REAL2> Real2D;
typedef thrust::device_vector<REAL3> Real3D;

typedef thrust::host_vector<int> IntH;
typedef thrust::host_vector<REAL> RealH;
typedef thrust::host_vector<REAL2> Real2H;

typedef thrust::device_vector<verttype> PointTypeD;
typedef thrust::device_ptr<verttype> PointTypeDPtr;
typedef thrust::host_vector<verttype> PointTypeH;

typedef thrust::device_vector<tethandle> TetHandleD;
typedef thrust::device_ptr<tethandle> TetHandleDPtr;
typedef thrust::host_vector<tethandle> TetHandleH;

typedef thrust::device_vector<trihandle> TriHandleD;
typedef thrust::device_ptr<trihandle> TriHandleDPtr;
typedef thrust::host_vector<trihandle> TriHandleH;

typedef thrust::device_vector<tetstatus> TetStatusD;
typedef thrust::device_ptr<tetstatus> TetStatusDPtr;
typedef thrust::host_vector<tetstatus> TetStatusH;

typedef thrust::device_vector<tristatus> TriStatusD;
typedef thrust::device_ptr<tristatus> TriStatusDPtr;
typedef thrust::host_vector<tristatus> TriStatusH;

typedef thrust::device_vector<int2>IntPairD;

typedef thrust::device_vector<unsigned long long>ULongLongD;

// Operators
struct isNotNegativeInt
{
	__device__ bool operator()(const int x)
	{
		return !(x < 0);
	}
};

struct isNegativeInt
{
	__device__ bool operator()(const int x)
	{
		return (x < 0);
	}
};

struct isNotNegativeByte
{
	__device__ bool operator()(const char x)
	{
		return !(x < 0);
	}
};

struct isEmptyTet
{
	__device__ bool operator()(const tetstatus x)
	{
		return x.isEmpty();
	}
};

struct isNotEmptyTet
{
	__device__ bool operator()(const tetstatus x)
	{
		return !(x.isEmpty());
	}
};

struct isBadTet
{
	__device__ bool operator()(const tetstatus x)
	{
		return (!x.isEmpty() && x.isBad());
	}
};

struct isAbortiveTet
{
	__device__ bool operator()(const tetstatus x)
	{
		return (!x.isEmpty() && x.isAbortive());
	}
};

struct isEmptyTri
{
	__device__ bool operator()(const tristatus x)
	{
		return x.isEmpty();
	}
};

struct isNotEmptyTri
{
	__device__ bool operator()(const tristatus x)
	{
		return !(x.isEmpty());
	}
};

// Active list maintenance
int updateActiveListByMarker_Slot
(
	IntD	    &t_marker,
	IntD		&t_active,
	int         numberofelements
);

int updateActiveListByMarker_Slot
(
	ByteD	    &t_marker,
	IntD		&t_active,
	int         numberofelements
);

int updateActiveListByStatus_Val
(
	IntD		&t_input,
	TriStatusD	&t_status,
	IntD		&t_active,
	int			numberofelements
);

int updateActiveListByStatus_Slot
(
	TetStatusD	&t_status,
	IntD		&t_active,
	int			numberofelements
);

int updateEmptyTets
(
	TetStatusD	&t_tetstatus,
	IntD	&t_emptytets
);

int updateEmptyTris
(
	TriStatusD &t_tristatus,
	IntD	&t_emptytris
);

void gpuMemoryCheck();