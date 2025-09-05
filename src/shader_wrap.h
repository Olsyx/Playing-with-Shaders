#pragma once
#include "raylib.h"
#include "light.h"

typedef class ShaderWrap {

	Shader _shader;

	public:		
		ShaderWrap(const char* vs, const char* fs);
		Shader* Unwrap();
		void CleanUp();

		void UpdateDirectionalLight(Light& light);
		void SetFloat(const char* key, float& value);
		void SetVector2(const char* key, Vector2& value);
		void SetVector3(const char* key, Vector3& value);
		void SetVector4(const char* key, Vector4& value);
};