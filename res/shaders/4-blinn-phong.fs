#version 330

out vec4 finalColor;

in vec4 fragColor;
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 uv;

uniform sampler2D texture0;

uniform vec4 colDiffuse;     // The tint passed when drawing

uniform float smoothness;
uniform vec3 specularTint;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 ambientColor;
uniform float ambientStrength;

void main() 
{
    vec3 albedo = texture(texture0, uv).rgb * colDiffuse.rgb;
    float monochrome = max(specularTint.r, max(specularTint.g, specularTint.b));
    albedo *= 1 - monochrome * 0.5;

    // Predefined light directions, like sunlight, need to be inverted
    vec3 L = normalize(-lightDir); 
    vec3 N = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPosition);
    
    vec3 diffuse = albedo * ambientColor * max(0, dot(N, L));

    vec3 halfVector = normalize(L + viewDir);
    float onlySpecular = max(0, dot(halfVector, N));
    vec3 specular = specularTint * ambientColor * pow(onlySpecular, smoothness * 100);

    finalColor = vec4(diffuse + specular, fragColor.a);
}