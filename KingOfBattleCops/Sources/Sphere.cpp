#include "stdafx.h"
#include "Sphere.h"

void Sphere::Init_And_Render(int model)
{
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(0.0, 0.0, 0.0));
    m_transform = glm::scale(m_transform, glm::vec3(1.5, 1.5, 1.5));

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}
