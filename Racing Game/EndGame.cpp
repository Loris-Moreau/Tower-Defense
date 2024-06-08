#include "EndGame.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"

EndGame::EndGame()
{
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = &Assets::getMesh("Mesh_Cube");
    mc->setMesh(*mesh);
    box = new BoxComponent(this);
    box->setObjectBox(mesh->getBox());
}

EndGame::~EndGame() = default;
