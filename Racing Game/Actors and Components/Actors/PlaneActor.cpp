#include "PlaneActor.h"
#include "..\Components\MeshComponent.h"
#include "..\..\Main\Assets.h"
#include "..\..\Main\Game.h"
#include "..\Components\BoxComponent.h"

PlaneActor::PlaneActor() : Actor()
{
	setScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = &Assets::getMesh("Mesh_Plane");
	mc->setMesh(*mesh);
	box = new BoxComponent(this);
	box->setObjectBox(mesh->getBox());

	getGame().addPlane(this);
}

PlaneActor::~PlaneActor()
{
	getGame().removePlane(this);
}
