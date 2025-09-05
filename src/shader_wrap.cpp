#include "shader_wrap.h"


ShaderWrap::ShaderWrap(const char* vs, const char* fs)
{
	_shader = LoadShader(vs, fs);
}

Shader* ShaderWrap::Unwrap() 
{
	return &_shader;
}

void ShaderWrap::CleanUp()
{
	UnloadShader(_shader);
}

void ShaderWrap::UpdateDirectionalLight(Light& light)
{
	SetVector3("dirLight.direction", light.direction);
	SetVector3("dirLight.color", light.color);
	SetFloat("dirLight.intensity", light.intensity);
}

void ShaderWrap::SetFloat(const char* key, float& value)
{
	int index = GetShaderLocation(_shader, key);
	SetShaderValue(_shader, index, &value, SHADER_ATTRIB_FLOAT);
}

void ShaderWrap::SetVector2(const char* key, Vector2& value)
{
	int index = GetShaderLocation(_shader, key);
	SetShaderValue(_shader, index, &value, SHADER_ATTRIB_VEC2);
}

void ShaderWrap::SetVector3(const char* key, Vector3& value)
{
	int index = GetShaderLocation(_shader, key);
	SetShaderValue(_shader, index, &value, SHADER_ATTRIB_VEC3);
}

void ShaderWrap::SetVector4(const char* key, Vector4& value)
{
	int index = GetShaderLocation(_shader, key);
	SetShaderValue(_shader, index, &value, SHADER_ATTRIB_VEC4);
}