#include "CubeActor.h"
#include "..\Components/MeshComponent.h"
#include "..\..\Main/Assets.h"

CubeActor::CubeActor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
}
