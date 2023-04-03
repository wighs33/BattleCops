#include "stdafx.h"
#include "Cube.h"

void Cube::Init_And_Render(int model) {
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.0, -5.0));
    m_transform = glm::scale(m_transform, glm::vec3(8.0, 8.0, 8.0));

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}

void Sky::Init_And_Render(int model) {
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.0, -50.0));
    m_transform = glm::scale(m_transform, glm::vec3(50.0, 50.0, 50.0));

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}

void Field::Init_And_Render(int model)
{
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(0.0, -1.0f / 2, 0.0));
    m_transform = glm::scale(m_transform, glm::vec3(30.0f, 30.0f, 30.0f));
    m_transform = glm::translate(m_transform, glm::vec3(0.0, -1.0f / 2, 0.0));

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}

void Lobby::Init_And_Render(int model)
{
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(20.0, -1.5f, 0.0));
    m_transform = glm::scale(m_transform, glm::vec3(10.0f, 10.0f, 30.0f));
    m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.5f, 0.0));

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}

void Lobby_Floor::Init_And_Render(int model)
{
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(20.0, -0.5f, 0.0));
    m_transform = glm::scale(m_transform, glm::vec3(10.0f, 10.0f, 30.0f));
    m_transform = glm::translate(m_transform, glm::vec3(0.0, -0.5f, 0.0));

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}

void Door::Init_And_Render(int model)
{
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(15.0f, -0.5f, 0.0));
    m_transform = glm::scale(m_transform, glm::vec3(0.1f, 2.0f, 1.0f));
    m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.5f, 0.0));

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}
