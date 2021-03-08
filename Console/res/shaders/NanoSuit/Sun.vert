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
uniform mat4 uMatriceRotation;
uniform vec3 uPlayerPos;
uniform float utime;
uniform float uGoingUp;
uniform float uTime2;

void main()
{

    float x = aPos.x  + uPlayerPos.x + 150;
    float y = aPos.y ;
    float z = aPos.z + uPlayerPos.z  + 150;

    x = aPos.x * cos(utime) - (aPos.y + 250) * sin(utime);
    y = aPos.x * sin(utime) + (aPos.y + 250) * cos(utime);

    vec4 pos = vec4(vec3(x +  uPlayerPos.x  , y , z ), 1.0);

    TexCoords = aTexCoords;
    playerPos = uPlayerPos;
    time = utime;
    time2 = uTime2;
    isGoingUp = uGoingUp;
    gl_Position =  projection * view * model  * pos ;
    //FragPos = vec3(model * vec4(aPos, 1.0) );
    normal = aNormal;

}
