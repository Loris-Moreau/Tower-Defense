#include "CubeActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Game.h"
#include "BoxComponent.h"

CubeActor::CubeActor() : Actor()
{
	setScale(1.0f);
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = &Assets::getMesh("Mesh_Cube");
	mc->setMesh(*mesh);
	box = new BoxComponent(this);
	//box->setShouldRotate(true);
	box->setObjectBox(mesh->getBox());

	getGame().addActor(this);
}

CubeActor::~CubeActor()
{
	getGame().removeActor(this);
}
