#version 430 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 FragPos;
in float time;
in float time2;
in float isGoingUp;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;


void main()
{

  float y = min(time * 500 - 250, 399); //350  is the sky limit so 399-50 is the last pixel we can see
  float x = 0;                          //time is between -0.2;1.8
  float z =  100;

  x = isGoingUp < 0 ? -500 : 450;

  if(y == 399){
    x = min((-time2) * 1.2f  + 575 , 450);
    x = max(x, -500);
  }


  if((( FragPos.y < y + 50 && FragPos.y > y - 50 )
    && (FragPos.z < z + 50 && FragPos.z > z - 50)))
   {
      if(y == 399 && FragPos.x < x + 50 && FragPos.x > x - 50){  FragColor = vec4(0.99f,0.78f,0.05f,1);}
      else if(y < 399 &&FragPos.x < x + 50 && FragPos.x > x - 50){ FragColor = vec4(0.99f,0.78f,0.05f,1);}
      else{
        float blue = (FragPos.y * 0.0002f);
        FragColor = vec4(0.53f,0.85f,0.98f,1) *(1-blue) * time ;
      }
   }
  else{
    float blue = (FragPos.y * 0.0002f);
    FragColor = vec4(0.53f,0.85f,0.98f,1) *(1-blue) * time ;
  }

}
