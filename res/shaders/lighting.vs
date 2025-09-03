// From raylib's examples
#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

uniform mat4 mvp;   // mvp = Projection * View * Model
uniform mat4 matModel;
uniform mat4 matNormal;

out vec4 fragColor;
out vec3 fragPosition;
out vec3 fragNormal;
out vec2 uv;

void main()
{
    fragColor    = vertexColor;
    fragPosition = vec3(matModel * vec4(vertexPosition, 1.0));
    fragNormal   = normalize(vec3(matNormal * vec4(vertexNormal, 0.0)));
    uv           = vertexTexCoord;

    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
