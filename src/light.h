#pragma once
#include "raylib.h"

typedef struct Light
{
	Vector3 Position;
	Vector3 Direction;
	Vector3 Color;
	float Strength;
};