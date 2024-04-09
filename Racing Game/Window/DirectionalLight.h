#pragma once

#include "..\Maths\Vector3.h"

struct DirectionalLight
{
	Vector3 direction;
	Vector3 diffuseColor;
	Vector3 specColor;
};