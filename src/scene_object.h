#pragma once
#include "raylib.h"
#include "raymath.h"
#include "all_textures.h"

typedef class SceneObject
{
	Vector3 _localForward;	
	Vector3 _worldForward;
	Transform _transform;	// Keeps object's world pos, quaternion and scale
	Model _model;			// Its transform is the object's transformation matrix, we need _transform to keep the data
	
	Matrix _transformMatrix; // Cached at draw time when something changed prior.
	bool _dirty = true;		 // Set to true when any transformations are applied to the SceneObject

public:
	void Load(const char* pathToModel);
	void Load(Mesh mesh);
	void SetTexture(MaterialMapIndex index, TextureIds textureId);

	void SetShader(Shader& shader);
	void SetTransform(Vector3 position, Vector3 rotation, float scale = 1);
	void SetForward(Vector3 newForward);

	void CleanUp();

	void LookAt(Vector3 target);
	void SetRotation(Vector3 degrees);

	Matrix GetTransformMatrix();
	void Draw(Color tint = WHITE);

};