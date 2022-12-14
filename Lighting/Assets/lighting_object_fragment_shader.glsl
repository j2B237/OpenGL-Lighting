#version 330 core

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 Normal;
in vec3 FragPos;

out vec3 norm;
out vec3 lightDir;

uniform vec3 lightPos;

void main()
{
	// Calculating the diffuse color

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max( dot(norm, lightDir), 0.0 );
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.4;
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = (ambient + diffuse ) * objectColor ;

	FragColor = vec4( result , 1.0f);
}