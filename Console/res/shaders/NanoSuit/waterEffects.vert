#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{
  if(time > 0){
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(vec3((sin(1.4 * aPos.y + time/1000.0 ) * cos(1.2 * aPos.z + time/1000.0) * 0.2) + aPos.x, (sin(1.4 * aPos.x + time/1000.0 ) * cos(1.2 * aPos.y + time/1000.0) * 0.2) + 9, aPos.z), 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    normal = aNormal;
  }

}



  //  FragPos.y = (sin(2.0 * FragPos.x + time/1000.0 ) * cos(1.5 * FragPos.y + time/1000.0) * 0.2);
