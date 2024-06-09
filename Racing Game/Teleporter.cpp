#include "Teleporter.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"

Teleporter::Teleporter()
{
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = &Assets::getMesh("Mesh_Teleporter");
    mc->setMesh(*mesh);

    //add collision bax
    box = new BoxComponent(this);
    box->setObjectBox(mesh->getBox());
}  
Teleporter::~Teleporter() = default;
