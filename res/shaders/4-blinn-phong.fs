#version 330

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

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
uniform DirectionalLight dirLight;

void main() 
{
    vec3 albedo = texture(texture0, uv).rgb * colDiffuse.rgb;
    float monochrome = max(specularTint.r, max(specularTint.g, specularTint.b));
    albedo *= 1 - monochrome * 0.5;

    // Predefined light directions, like sunlight, need to be inverted
    vec3 L = normalize(-dirLight.direction); 
    vec3 N = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPosition);
    
    vec3 dirRadiance = dirLight.color * dirLight.intensity;

    vec3 diffuse = albedo * dirRadiance * max(0, dot(N, L));

    vec3 halfVector = normalize(L + viewDir);
    float specular = max(0, dot(halfVector, N));
    specular = pow(specular, smoothness * 100);
    vec3 specularColor = specular * specularTint * dirRadiance * dirLight.intensity;

    finalColor = vec4(diffuse + specularColor, fragColor.a);
}