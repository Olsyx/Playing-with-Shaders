#include "raylib.h"
#include "raymath.h"

#include "all_textures.h"
#include "light.h"
#include "scene_object.h"

Camera InitCamera() 
{
    Camera camera = { 0 };
    camera.position = Vector3{ 25.0f, 25.0f, 25.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f; // Field of View Y
    camera.projection = CAMERA_PERSPECTIVE;

    return camera;
}

Light InitLight() 
{
    Light light;
    light.Position = Vector3{ 0.0f, 10.0f, 10.0f };
    light.Direction = Vector3{ 0.0f, -1.0f, -1.0f };
    light.Color = Vector3{ 1.0f, 0.75f, 0.0f };
    light.Strength = 0.1f;
    return light;
}

void UpdateShader(Shader* shader, Camera& camera, Light& light)
{

    int loc = GetShaderLocation(*shader, "viewPos");
    SetShaderValue(*shader, loc, &camera.position, SHADER_UNIFORM_VEC3);

    loc = GetShaderLocation(*shader, "lightPos");
    SetShaderValue(*shader, loc, &light.Position, SHADER_UNIFORM_VEC3);

    loc = GetShaderLocation(*shader, "lightDir");
    SetShaderValue(*shader, loc, &light.Direction, SHADER_UNIFORM_VEC3);

    loc = GetShaderLocation(*shader, "ambientColor");
    SetShaderValue(*shader, loc, &light.Color, SHADER_UNIFORM_VEC3);

    loc = GetShaderLocation(*shader, "ambientStrength");
    SetShaderValue(*shader, loc, &light.Strength, SHADER_ATTRIB_FLOAT);

    float smoothness = 0.2;
    loc = GetShaderLocation(*shader, "smoothness");
    SetShaderValue(*shader, loc, &smoothness, SHADER_ATTRIB_FLOAT);

    float metallic = 0.2;
    loc = GetShaderLocation(*shader, "metallic");
    SetShaderValue(*shader, loc, &metallic, SHADER_ATTRIB_FLOAT);

    /*Vector3 specularTint = Vector3{1.0, 1.0, 1.0};
    loc = GetShaderLocation(*shader, "specularTint");
    SetShaderValue(*shader, loc, &specularTint, SHADER_UNIFORM_VEC3);*/


}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib 5.5 - playing with shaders by Olsyx");
    SetTargetFPS(60);               

    AllTextures::Init();
    Camera camera = InitCamera();
    Light light = InitLight();

    Shader shader = LoadShader("res/shaders/lighting.vs", "res/shaders/4-blinn-phong.fs");
    UpdateShader(&shader, camera, light);

    SceneObject lightSO;
    lightSO.Load(GenMeshCone(1, 2, 5));
    lightSO.SetTransform(light.Position, Vector3{ 0.0, 0.0, 0.0 });
    lightSO.SetForward(Vector3{ 0.0, -1.0, 0.0 });
    lightSO.LookAt(light.Direction);

    SceneObject targetSO;
    targetSO.Load(GenMeshSphere(3, 16, 16));
    targetSO.SetTexture(MATERIAL_MAP_ALBEDO, TextureIds::Checkerboard);
    targetSO.SetTransform(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 90.0, 0.0, 0.0 });
    targetSO.SetShader(shader);

    while (!WindowShouldClose())    
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        UpdateShader(&shader, camera, light);

        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginMode3D(camera);
                lightSO.Draw(RED);
                targetSO.Draw(WHITE);
                DrawGrid(20, 10.0f);
            EndMode3D();

            DrawFPS(10, 10);
        EndDrawing();
    }

    lightSO.CleanUp();
    targetSO.CleanUp();
    UnloadShader(shader);

    AllTextures::CleanUp();
    CloseWindow();       

    return 0;
}
