#version 330

out vec4 finalColor;

in vec4 fragColor;
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;      // interpolated UV from vertex shader

uniform sampler2D texture0; // Diffuse map
uniform vec4 colDiffuse;    // The tint passed when drawing


void main() 
{
    vec4 texel = texture(texture0, fragTexCoord);
    finalColor = texel + colDiffuse;
}