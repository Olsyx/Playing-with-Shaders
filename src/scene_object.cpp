#include "scene_object.h"


void SceneObject::Load(const char* pathToModel)
{
    _model = LoadModel(pathToModel);
}

void SceneObject::Load(Mesh mesh)
{
   _model = LoadModelFromMesh(mesh);
}

void SceneObject::SetTexture(MaterialMapIndex index, TextureIds textureId)
{
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *AllTextures::Get(textureId);
}

void SceneObject::SetShader(Shader shader)
{
    _model.materials[0].shader = shader;
}

void SceneObject::CleanUp()
{
    // AllTextures unloads Textures
    UnloadModel(_model);
}

void SceneObject::SetTransform(Vector3 position, Vector3 degrees, float scale)
{
    Vector3 rotation = Vector3{ DEG2RAD * degrees.x, DEG2RAD * degrees.y, DEG2RAD * degrees.z };

    _transform.translation = position;
    _transform.scale = { scale, scale, scale };
    _transform.rotation = QuaternionFromEuler(rotation.x, rotation.y, rotation.z);

    _worldForward = Vector3RotateByQuaternion(_localForward, _transform.rotation);

    // Update mesh's transformation matrix
    Matrix matScale = MatrixScale(_transform.scale.x, _transform.scale.y, _transform.scale.z);
    Matrix matRot = QuaternionToMatrix(_transform.rotation);
    Matrix matTrans = MatrixTranslate(position.x, position.y, position.z);

    _model.transform = MatrixMultiply(MatrixMultiply(matScale, matRot), matTrans);
}

void SceneObject::SetForward(Vector3 localForward)
{
    _localForward = localForward;
    Vector3 worldForward = Vector3Transform(_localForward, QuaternionToMatrix(_transform.rotation));
    _worldForward = Vector3Normalize(worldForward);
}

void SceneObject::LookAt(Vector3 target) 
{
    Vector3 direction = Vector3Normalize(Vector3Subtract(target, _transform.translation));
    Quaternion rot = QuaternionFromVector3ToVector3(_worldForward, direction);

    Matrix rotation = QuaternionToMatrix(rot);
    _model.transform = MatrixMultiply(rotation, _model.transform);
}

void SceneObject::SetRotation(Vector3 degrees)
{
    Vector3 rotation = Vector3{ DEG2RAD * degrees.x, DEG2RAD * degrees.y, DEG2RAD * degrees.z };
    _model.transform = MatrixRotateXYZ(rotation);
    _transform.rotation = QuaternionFromEuler(rotation.x, rotation.y, rotation.z);
    _worldForward = Vector3RotateByQuaternion(_localForward, _transform.rotation);
}

void SceneObject::Draw(Color tint)
{
    for (int i = 0; i < _model.meshCount; i++)
    {
        Material mat = _model.materials[_model.meshMaterial[i]];
        Color previousColor = mat.maps[MATERIAL_MAP_DIFFUSE].color;

        mat.maps[MATERIAL_MAP_DIFFUSE].color = tint;
        DrawMesh(_model.meshes[i], mat, _model.transform);
        mat.maps[MATERIAL_MAP_DIFFUSE].color = previousColor;
    }
}
