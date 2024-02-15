#include "SplineActor.h"
#include "SplineCameraComponent.h"

SplineActor::SplineActor() : Actor(), cameraComponent(nullptr)
{
	cameraComponent = new SplineCameraComponent(this);

	// Create a spline
	Spline spline;
	spline.controlPoints.emplace_back(Vector3::zero);
	for (int i = 0; i < 5; i++)
	{
		if (i % 2 == 0)
		{
			spline.controlPoints.emplace_back(Vector3(0,0,0));
		}
		else
		{
			spline.controlPoints.emplace_back(Vector3(0,1000,20));
		}
	}

	cameraComponent->setSpline(spline);
	cameraComponent->setPaused(false);
}

void SplineActor::actorInput(const InputState& inputState)
{

}

void SplineActor::restartSpline()
{
	cameraComponent->restart();
}
