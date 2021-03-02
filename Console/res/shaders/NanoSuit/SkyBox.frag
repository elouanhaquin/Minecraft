#version 430 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 FragPos;
in float time;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;


void main()
{
  float blue = (FragPos.y * 0.0002f);
  FragColor = vec4(0.53f,0.85f,0.98f,1) *(1-blue) * time ;


}
