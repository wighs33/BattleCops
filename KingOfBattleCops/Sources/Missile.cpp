#include "stdafx.h"
#include "Missile.h"

void Missile::Init_And_Render(int model)
{
    glm::mat4 m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, pos);

    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_transform));

    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, NUMOF_VERTICES);
}
