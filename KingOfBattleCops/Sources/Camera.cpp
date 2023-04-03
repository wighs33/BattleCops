#include "stdafx.h"
#include "Camera.h"

void Camera::Init_View()
{
	cameraDirection = glm::vec3(cameraPos.x, cameraPos.y / 2 - 1.0, cameraPos.z - 10.0);
	v_transform = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(v_transform));
	glUniform3fv(cameraPos_loc, 1, (float*)&cameraPos);
}

void Camera::Init_Projection() {
	p_transform = glm::perspective(glm::radians(60.0f), WIN_W / WIN_H, 0.001f, 1000.f);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(p_transform));
}
