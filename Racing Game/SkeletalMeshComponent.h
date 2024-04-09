#pragma once
#include "MeshComponent.h"
#include "MatrixPalette.h"
class SkeletalMeshComponent : public MeshComponent
{
public:
	SkeletalMeshComponent(Actor* owner);

	void setSkeleton(const class Skeleton& skeletonP);

	void update(float dt) override;
	void draw(class Shader& shader) override;

	// Play an animation. Returns the length of the animation
	float playAnimation(const class Animation* anim, float playRate = 1.0f);

protected:
	void computeMatrixPalette();

	MatrixPalette palette;
	const class Skeleton* skeleton;
	const class Animation* animation;
	float animPlayRate;
	float animTime;
};

