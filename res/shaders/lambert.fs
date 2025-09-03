#version 330

out vec4 finalColor;

in vec4 fragColor;
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 uv;

uniform sampler2D texture0;

uniform vec4 colDiffuse;     // The tint passed when drawing

uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 ambientColor;
uniform float ambientStrength;

void main() 
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightDir);

     // Predefined light directions, like sunlight, need to be inverted
    float lambert = max(0, dot(N, -L));

    vec3 albedo = texture(texture0, uv).rgb;
    albedo *= colDiffuse;

    vec3 diffuse = albedo * ambientColor * lambert;
    finalColor = vec4(diffuse, fragColor.a);
}