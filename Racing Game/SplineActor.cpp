#include "SplineActor.h"
#include "SplineCameraComponent.h"

SplineActor::SplineActor() : Actor(), cameraComponent(nullptr)
{
	cameraComponent = new SplineCameraComponent(this);

	// Create a spline
	Spline spline;
	spline.controlPoints.emplace_back(Vector3::zero);
	for (int i = 0; i < 50; i++)
	{
		if (i % 2 == 0)
		{
			spline.controlPoints.emplace_back(Vector3(300.0f * (i + 1), 500.0f, 500.0f));
		}
		else
		{
			spline.controlPoints.emplace_back(Vector3(300.0f * (i + 1), 500.0f, 500.0f));
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