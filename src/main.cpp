#include "raylib.h"
#include "light.h"

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
    light.Color = Vector3{ 1.0f, 1.0f, 1.0f };
    light.Strength = 0.1f;
    return light;
}

Shader InitShader(Light &light) 
{
    Shader shader = LoadShader("res/shaders/vertex_basic.glsl", "res/shaders/fragment_pbr.glsl");

    int loc = GetShaderLocation(shader, "lightPos");
    SetShaderValue(shader, loc, &light.Position, SHADER_UNIFORM_VEC3);

    loc = GetShaderLocation(shader, "lightDir");
    SetShaderValue(shader, loc, &light.Direction, SHADER_UNIFORM_VEC3);

    loc = GetShaderLocation(shader, "ambientColor");
    SetShaderValue(shader, loc, &light.Color, SHADER_UNIFORM_VEC3);

    loc = GetShaderLocation(shader, "ambientStrength");
    SetShaderValue(shader, loc, &light.Strength, SHADER_ATTRIB_FLOAT);

    return shader;
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    const char* modelPath = "res/models/Icosphere.obj";
    const char* mainTexPath = "res/textures/checkerboard.jpg";

    InitWindow(screenWidth, screenHeight, "raylib 5.5 - playing with shaders by Olsyx");
    SetTargetFPS(60);               

    Camera camera = InitCamera();
    Light light = InitLight();

    Model lightGizmoModel = LoadModel(modelPath);

    Model model = LoadModel(modelPath);
    Texture2D mainTex = {};
    if (mainTexPath != "") {
        mainTex = LoadTexture(mainTexPath);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = mainTex;
    }

    Vector3 modelPos = Vector3{ 0.0f, 0.0f, 0.0f };

    Shader shader = InitShader(light);
    model.materials[0].shader = shader;


    while (!WindowShouldClose())    
    {
        //UpdateCamera(&camera, CAMERA_ORBITAL);
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawModel(lightGizmoModel, light.Position, 1.0f, RED);
                DrawModel(model, modelPos, 3.0f, WHITE);
                DrawGrid(20, 10.0f);
            EndMode3D();

            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadTexture(mainTex);
    UnloadModel(model);
    UnloadShader(shader);
    CloseWindow();       

    return 0;
}
