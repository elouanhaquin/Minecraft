#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 normal;
out vec3 FragPos;
out vec3 playerPos;

out float time;
out float time2;
out float isGoingUp;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 uPlayerPos;
uniform float utime;
uniform float uGoingUp;
uniform float uTime2;

void main()
{

    TexCoords = aTexCoords;


    float x =  aPos.x;
    float y = aPos.y;
    float z = aPos.z;

  /*  if(x < 100 && x >0 && y < 100 && y > 0){
       x = x*cos(uTime2) - y*sin(uTime2);
       y = x*sin(uTime2) + y*cos(uTime2) + 100;
      // z = (sin(waveHeight * aPos.x + time*5 ) * cos(waveHeight * aPos.y + time*5) * 0.05) + aPos.z;
    }*/

    playerPos = uPlayerPos;

    time = utime;
    time2 = uTime2;
    isGoingUp = uGoingUp;
    gl_Position = projection * view * model * vec4(vec3(x, y , z), 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    normal = aNormal;

}



  //  FragPos.y = (sin(2.0 * FragPos.x + time/1000.0 ) * cos(1.5 * FragPos.y + time/1000.0) * 0.2);
