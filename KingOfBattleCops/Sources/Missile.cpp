#include "stdafx.h"
#include "Missile.h"

void Missile::Init_And_Render(int model)
{
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, pos);
    m_transform = glm::rotate(m_transform, glm::radians(y_rotate), glm::vec3(0.0, 1.0, 0.0));
    m_transform = glm::rotate(m_transform, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}
