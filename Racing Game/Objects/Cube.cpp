#include "Cube.h"
#include "..\Actors and Components/Components/MeshComponent.h"
#include "..\Main/Assets.h"

Cube::Cube()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
}