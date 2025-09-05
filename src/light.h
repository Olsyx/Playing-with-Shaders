#pragma once
#include "raylib.h"

typedef enum LightTypes {
	Directional, Point, Spotlight
};

typedef struct Light
{
	Vector3 position;
	LightTypes type;
	Vector3 direction;
	Vector3 color;
	float intensity;
};