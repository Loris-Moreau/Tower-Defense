#pragma once
#include "UIScreen.h"

class HUD : public UIScreen
{
public:
	HUD();
	~HUD();
	
	void update(float dt) override;
	void draw(class Shader& shader) override;
	void addTargetComponent(class TargetComponent* tc);
	void removeTargetComponent(class TargetComponent* tc);
	
protected:
	void updateCrosshair(float deltaTime);
	void updateRadar(float deltaTime);
	Texture* crosshair;

	Texture* crosshairEnemy;
	Texture* radar;
	Texture* blipTex;
	Texture* radarArrow;
	
	std::vector<TargetComponent*> targetComponents;
	bool isTargetingEnemy;
	
	vector<Vector2> blips;
	float radarRange;
	float radarRadius;
};