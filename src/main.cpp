#include "raylib.h"
#include "raymath.h"

#include "light.h"
#include "all_textures.h"
#include "all_scene_objects.h"
#include "shader_wrap.h"
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
    light.position = Vector3{ 0.0f, 10.0f, 10.0f };
    light.direction = Vector3{ 0.0f, -1.0f, -1.0f };
    light.color = Vector3{ 1.0f, 0.75f, 0.0f };
    light.intensity = 1.0f;
    return light;
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib 5.5 - playing with shaders by Olsyx");
    SetTargetFPS(60);               

    AllTextures::Init();
    AllSceneObjects::Init();
    Camera camera = InitCamera();
    Light dirLight = InitLight();

    ShaderWrap shader("res/shaders/lighting.vs", "res/shaders/unlit_tex.fs");
    shader.UpdateDirectionalLight(dirLight);

    Handle dirLightHandle = AllSceneObjects::Load(GenMeshCone(1, 2, 5));
    Handle sphereHandle = AllSceneObjects::Load(GenMeshSphere(3, 16, 16));

    SceneObject* dirLightSO = AllSceneObjects::Get(dirLightHandle);
    dirLightSO->SetTransform(dirLight.position, Vector3{ 0.0, 0.0, 0.0 });
    dirLightSO->SetForward(Vector3{ 0.0, -1.0, 0.0 });
    dirLightSO->LookAt(dirLight.direction);

    SceneObject* sphereSO = AllSceneObjects::Get(sphereHandle);
    sphereSO->SetTexture(MATERIAL_MAP_ALBEDO, TextureIds::Checkerboard);
    sphereSO->SetTransform(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 90.0, 0.0, 0.0 });
    sphereSO->SetShader(*shader.Unwrap());

    float smoothness = 0.8;
    shader.SetFloat("smoothness", smoothness);

    Vector3 specularTint = Vector3{ 1.0f, 1.0f, 1.0f };
    shader.SetVector3("specularTint", specularTint);
    
    //float metallic = 0.8;
    //shader.SetFloat("metallic", metallic);

    while (!WindowShouldClose())    
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        shader.SetVector3("viewPos", camera.position);

        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginMode3D(camera);
                AllSceneObjects::Draw();
                DrawGrid(20, 10.0f);
            EndMode3D();

            DrawFPS(10, 10);
        EndDrawing();
    }

    shader.CleanUp();

    AllSceneObjects::CleanUp();
    AllTextures::CleanUp();
    CloseWindow();       

    return 0;
}
