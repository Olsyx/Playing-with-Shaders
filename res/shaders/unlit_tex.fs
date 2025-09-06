#version 330

out vec4 finalColor;

in vec4 fragColor;
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 uv;      

uniform sampler2D texture0; // Diffuse map
uniform vec4 colDiffuse;    // The tint passed when drawing


void main() 
{
    vec4 texel = texture(texture0, uv);
    finalColor = texel + colDiffuse;
}