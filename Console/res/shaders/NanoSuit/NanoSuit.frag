#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 FragPos;  

uniform sampler2D texture_diffuse1;

void main()
{    
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(vec3(0,-1,0) - FragPos);  

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * norm;
	//FragColor = vec4((normal + diffuse), 1);
	//FragColor = vec4(normal,1);
    FragColor = texture(texture_diffuse1, TexCoords);
}