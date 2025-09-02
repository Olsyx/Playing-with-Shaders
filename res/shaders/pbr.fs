#version 330

out vec4 finalColor;

in vec4 fragColor;
in vec3 fragPosition;
in vec3 fragNormal;

uniform vec4 colDiffuse;     // The tint passed when drawing

uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 ambientColor;
uniform float ambientStrength;

void main() 
{
    vec3 norm = normalize(fragNormal);
   
    vec3 ambient = ambientStrength * ambientColor;
     
    float diff = max(dot(norm, -lightDir), 0.0);
    
    vec3 diffuse = diff * ambientColor;

    //vec3 result = (ambient + diffuse) * fragColor.rgb;
    finalColor = vec4(colDiffuse.rgb * diffuse, fragColor.a);
}