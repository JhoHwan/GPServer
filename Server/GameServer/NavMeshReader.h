#pragma once
#include <cstdint>
#include "DetourNavMesh.h"

struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct NavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

class NavMeshReader
{
public:
	static dtNavMesh* DeSerializedtNavMesh(const char* path);

private:
	static const int NAVMESHSET_MAGIC;
	static const int NAVMESHSET_VERSION;
};

