#version 330

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

out vec3 frag_normal;
out vec3 frag_worldPos; 
out vec2 TexCoord;

uniform mat4 g_model;
uniform mat4 g_view;
uniform mat4 g_projection;

void main(void)
{
	vec4 worldPos = g_model * vec4(in_position, 1.0);
	gl_Position = g_projection * g_view * worldPos;

	vec4 worldNormal = g_model * vec4(in_normal, 0.0);
	frag_normal = vec3(worldNormal.x, worldNormal.y, worldNormal.z);
	frag_worldPos = vec3(worldPos);

	TexCoord = in_uv;
}