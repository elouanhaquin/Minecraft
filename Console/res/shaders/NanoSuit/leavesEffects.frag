#version 430 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 FragPos;
in float oTime;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;


void main()
{
  vec3 norm = -normalize(normal);
  vec3 lightDir = normalize(vec3(lightPos.x * oTime, lightPos.y * oTime, lightPos.z * oTime)  - FragPos);

  float diff = max(dot(norm, lightDir),0.1);
  vec3 diffuse = diff * vec3(1,1,1);
  vec4 result = vec4(diffuse,1.0) * 1;

  FragColor =  texture(texture_diffuse1, TexCoords)  ;
  FragColor = result  * FragColor ;
}
