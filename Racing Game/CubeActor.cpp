#include "CubeActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Game.h"

CubeActor::CubeActor()
{
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = &Assets::getMesh("Mesh_Cube");
	mc->setMesh(*mesh);
	//mc->setMesh(Assets::getMesh("Mesh_Cube"));

	// Add collision box
	box = new BoxComponent(this);
	box->setObjectBox(mesh->getBox());
	//box->setShouldRotate(true);
	
	getGame().addActor(this);
}

CubeActor::~CubeActor()
{
	getGame().removeActor(this);
}

