#pragma once

class Camera
{
public:
	void Init() {
		Init_View();
		Init_Projection();
	}

	void Init_View();
	void Init_Projection();

	GLuint view_loc;
	GLuint cameraPos_loc;
	GLuint proj_loc;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 v_transform = glm::mat4(1.0f);

	glm::mat4 p_transform = glm::mat4(1.0f);

	double z_move;

	float rotation;
	float revolution;
};