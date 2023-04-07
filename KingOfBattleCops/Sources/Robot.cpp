#include "stdafx.h"
#include "Robot.h"

void Robot::Init_And_Render(int model) {
	Init_And_Render_Left_Leg(model);
	Init_And_Render_Right_Leg(model);
	Init_And_Render_Torso(model);
	Init_And_Render_Left_Arm(model);
	Init_And_Render_Right_Arm(model);
	Init_And_Render_Head(model);
	Init_And_Render_Nose(model);
}

void Robot::Init_And_Render_Left_Leg(int model) {
	//누적되어도 변환은 거꾸로 계산된다!

	glm::mat4 m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, pos);
	if (state == DIE && (dir == DIR_FRONT || dir == DIR_BACK)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	}
	if (state == DIE && (dir == DIR_LEFT || dir == DIR_RIGHT)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	}
	m_transform = glm::rotate(m_transform, glm::radians(y_rotate), glm::vec3(0.0, 1.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.0, -0.1, 0.0));
	m_transform = glm::rotate(m_transform, glm::radians(x_rotate), glm::vec3(1.0, 0.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(-0.1, -0.2, 0.0));
	m_transform = glm::scale(m_transform, glm::vec3(0.1, 0.4, 0.1));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));
	glBindVertexArray(bodies[LEFT_LEG].VAO_ID);
	glDrawArrays(GL_TRIANGLES, 0, Cube::NUMOF_VERTICES);
}

void Robot::Init_And_Render_Right_Leg(int model) {
	glm::mat4 m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, pos);
	if (state == DIE && (dir == DIR_FRONT || dir == DIR_BACK)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	}
	if (state == DIE && (dir == DIR_LEFT || dir == DIR_RIGHT)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	}
	m_transform = glm::rotate(m_transform, glm::radians(y_rotate), glm::vec3(0.0, 1.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.0, -0.1, 0.0));
	m_transform = glm::rotate(m_transform, glm::radians(-x_rotate), glm::vec3(1.0, 0.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.1, -0.2, 0.0));
	m_transform = glm::scale(m_transform, glm::vec3(0.1, 0.4, 0.1));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));
	glBindVertexArray(bodies[RIGHT_LEG].VAO_ID);
	glDrawArrays(GL_TRIANGLES, 0, Cube::NUMOF_VERTICES);
}

void Robot::Init_And_Render_Torso(int model) {
	glm::mat4 m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, pos);
	if (state == DIE && (dir == DIR_FRONT || dir == DIR_BACK)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	}
	if (state == DIE && (dir == DIR_LEFT || dir == DIR_RIGHT)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	}
	m_transform = glm::rotate(m_transform, glm::radians(y_rotate), glm::vec3(0.0, 1.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.2, 0.0));
	m_transform = glm::scale(m_transform, glm::vec3(0.4, 0.6, 0.4));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));
	glBindVertexArray(bodies[TORSO].VAO_ID);
	glDrawArrays(GL_TRIANGLES, 0, Cube::NUMOF_VERTICES);
}

void Robot::Init_And_Render_Left_Arm(int model) {
	glm::mat4 m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, pos);
	if (state == DIE && (dir == DIR_FRONT || dir == DIR_BACK)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	}
	if (state == DIE && (dir == DIR_LEFT || dir == DIR_RIGHT)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	}
	m_transform = glm::rotate(m_transform, glm::radians(y_rotate), glm::vec3(0.0, 1.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.35, 0.0));
	m_transform = glm::rotate(m_transform, glm::radians(-x_rotate), glm::vec3(1.0, 0.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(-0.25, -0.15, 0.0));
	m_transform = glm::scale(m_transform, glm::vec3(0.1, 0.4, 0.1));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));
	glBindVertexArray(bodies[LEFT_ARM].VAO_ID);
	glDrawArrays(GL_TRIANGLES, 0, Cube::NUMOF_VERTICES);
}

void Robot::Init_And_Render_Right_Arm(int model) {
	glm::mat4 m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, pos);
	if (state == DIE && (dir == DIR_FRONT || dir == DIR_BACK)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	}
	if (state == DIE && (dir == DIR_LEFT || dir == DIR_RIGHT)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	}
	m_transform = glm::rotate(m_transform, glm::radians(y_rotate), glm::vec3(0.0, 1.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.35, 0.0));
	m_transform = glm::rotate(m_transform, glm::radians(x_rotate), glm::vec3(1.0, 0.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.25, -0.15, 0.0));
	m_transform = glm::scale(m_transform, glm::vec3(0.1, 0.4, 0.1));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));
	glBindVertexArray(bodies[RIGHT_ARM].VAO_ID);
	glDrawArrays(GL_TRIANGLES, 0, Cube::NUMOF_VERTICES);
}

void Robot::Init_And_Render_Head(int model) {
	glm::mat4 m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, pos);
	if (state == DIE && (dir == DIR_FRONT || dir == DIR_BACK)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	}
	if (state == DIE && (dir == DIR_LEFT || dir == DIR_RIGHT)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	}
	m_transform = glm::rotate(m_transform, glm::radians(y_rotate), glm::vec3(0.0, 1.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.6, 0.0));
	m_transform = glm::scale(m_transform, glm::vec3(0.2, 0.2, 0.2));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));
	glBindVertexArray(bodies[HEAD].VAO_ID);
	glDrawArrays(GL_TRIANGLES, 0, Cube::NUMOF_VERTICES);
}

void Robot::Init_And_Render_Nose(int model) {
	glm::mat4 m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, pos);
	if (state == DIE && (dir == DIR_FRONT || dir == DIR_BACK)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	}
	if (state == DIE && (dir == DIR_LEFT || dir == DIR_RIGHT)) {
		m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	}
	m_transform = glm::rotate(m_transform, glm::radians(y_rotate), glm::vec3(0.0, 1.0, 0.0));
	m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.6, 0.1));
	m_transform = glm::scale(m_transform, glm::vec3(0.05, 0.1, 0.05));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));
	glBindVertexArray(bodies[NOSE].VAO_ID);
	glDrawArrays(GL_TRIANGLES, 0, Cube::NUMOF_VERTICES);
}
