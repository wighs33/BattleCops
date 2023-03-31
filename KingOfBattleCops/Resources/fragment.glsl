#version 330 core

in vec3 frag_normal;
in vec3 frag_worldPos;
in vec2 TexCoord; 

out vec4 out_color;

uniform vec3 g_lightAmbient;
uniform vec3 g_lightPos;
uniform vec3 g_lightColor;
uniform vec3 g_objectColor;
uniform vec3 g_cameraPos;

uniform sampler2D texture1;

void main(void)
{	
	vec3 ambient = g_lightAmbient * g_lightColor;

	vec3 normalVector = normalize(frag_normal);
	vec3 lightDir = normalize(g_lightPos - frag_worldPos);
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);
	vec3 diffuse = diffuseLight * g_lightColor;

	int shininess = 128;
	vec3 viewDir = normalize(g_cameraPos - frag_worldPos);
	vec3 reflectDir = reflect(-lightDir, normalVector);
	float specularLight = max(dot(viewDir, reflectDir), 0.0);
	specularLight = pow(specularLight, shininess);
	vec3 specular = specularLight * g_lightColor;

	vec3 result = (ambient + diffuse + specular) * g_objectColor;

	out_color = vec4(result, 1.0);
	out_color = texture(texture1, TexCoord) * out_color;
}