#include "stdafx.h"
#include "Camera.h"

void Camera::Init_View()
{
	v_transform = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	//v_transform = glm::rotate(v_transform, glm::radians(rotation), glm::vec3(0.0, 1.0, 0.0));
	//v_transform = glm::translate(v_transform, glm::vec3(0.0, 0.0, -10.0f + z_move));
	//v_transform = glm::rotate(v_transform, glm::radians(revolution), glm::vec3(0.0, 1.0, 0.0));

	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(v_transform));
	glUniform3fv(cameraPos_loc, 1, (float*)&cameraPos);
}

void Camera::Init_Projection() {
	p_transform = glm::perspective(glm::radians(60.0f), WIN_W / WIN_H, 0.001f, 1000.f);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(p_transform));
}
