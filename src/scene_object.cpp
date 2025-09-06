#include "scene_object.h"

#pragma region Init & CleanUp
void SceneObject::Load(const char* pathToModel)
{
    ++_gen;
    _model = LoadModel(pathToModel);
}

void SceneObject::Load(Mesh mesh)
{
    ++_gen;
    _model = LoadModelFromMesh(mesh);
}

int SceneObject::GetGen() 
{
    return _gen;
}

void SceneObject::CleanUp()
{
    // AllTextures unloads Textures
    UnloadModel(_model);
}
#pragma endregion


void SceneObject::SetTexture(MaterialMapIndex index, TextureIds textureId)
{
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *AllTextures::Get(textureId);
}

void SceneObject::SetShader(Shader& shader)
{
    _model.materials[0].shader = shader;
}

#pragma region Transform Calculations
void SceneObject::SetTransform(Vector3 position, Vector3 degrees, float scale)
{
    _dirty = true;
    Vector3 rotation = Vector3{ DEG2RAD * degrees.x, DEG2RAD * degrees.y, DEG2RAD * degrees.z };

    _transform.translation = position;
    _transform.scale = { scale, scale, scale };
    _transform.rotation = QuaternionFromEuler(rotation.x, rotation.y, rotation.z);

    _worldForward = Vector3RotateByQuaternion(_localForward, _transform.rotation);
}

void SceneObject::SetForward(Vector3 localForward)
{
    _dirty = true;
    _localForward = localForward;
    Vector3 worldForward = Vector3Transform(_localForward, QuaternionToMatrix(_transform.rotation));
    _worldForward = Vector3Normalize(worldForward);
}

void SceneObject::LookAt(Vector3 target) 
{
    _dirty = true;
    Vector3 direction = Vector3Normalize(Vector3Subtract(target, _transform.translation));
    _transform.rotation = QuaternionFromVector3ToVector3(_worldForward, direction);
}

void SceneObject::SetRotation(Vector3 degrees)
{
    _dirty = true;
    Vector3 rotation = Vector3{ DEG2RAD * degrees.x, DEG2RAD * degrees.y, DEG2RAD * degrees.z };
    _transform.rotation = QuaternionFromEuler(rotation.x, rotation.y, rotation.z);
    _worldForward = Vector3RotateByQuaternion(_localForward, _transform.rotation);
}
#pragma endregion

Matrix SceneObject::GetTransformMatrix()
{
    Matrix pos = MatrixTranslate(_transform.translation.x, _transform.translation.y, _transform.translation.z);
    Matrix rot = QuaternionToMatrix(_transform.rotation);
    Matrix scale = MatrixScale(_transform.scale.x, _transform.scale.y, _transform.scale.z);
    return MatrixMultiply(MatrixMultiply(scale, rot), pos);
}

void SceneObject::Draw(Color tint)
{
    if (_dirty)
    {
        _transformMatrix = GetTransformMatrix();
        _dirty = false;
    }

    for (int i = 0; i < _model.meshCount; i++)
    {
        Material mat = _model.materials[_model.meshMaterial[i]];
        Color previousColor = mat.maps[MATERIAL_MAP_DIFFUSE].color;

        mat.maps[MATERIAL_MAP_DIFFUSE].color = tint;
        DrawMesh(_model.meshes[i], mat, _transformMatrix);
        mat.maps[MATERIAL_MAP_DIFFUSE].color = previousColor;
    }
}
