#include "SphereActor.h"
#include "..\Components\MeshComponent.h"
#include "..\..\Main\Assets.h"

SphereActor::SphereActor() : Actor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
}
