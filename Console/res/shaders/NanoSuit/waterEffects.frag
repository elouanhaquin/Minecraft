#version 430 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;


void main()
{
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - FragPos);

  float diff = max(dot(norm, lightDir),0.55);
  vec3 diffuse = diff * vec3(1,1,1);
  vec4 result = vec4(diffuse,1.0) * 0.7;

//FragColor = vec4(normal,1);
//FragColor *= vec4((normal + diffuse), 1) * 0.9;



  FragColor =  texture(texture_diffuse1, TexCoords)  ;
  FragColor = result  * FragColor ;
}
