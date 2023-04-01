#include "stdafx.h"
#include "Light.h"

void Light::Init() {
    glm::vec3 lightAmbient = LIGHT_AMBIENT;
    glUniform3fv(lightAmbient_loc, 1, (float*)&lightAmbient);

    glm::vec3 lightPos = glm::vec3(3 * cos(yRotate_light), 0.0, 3 * sin(yRotate_light));
    glUniform3fv(lightPos_loc, 1, (float*)&lightPos);

    glm::vec3 lightColor = LIGHT_COLOR;
    glUniform3fv(lightColor_loc, 1, (float*)&lightColor);

    glm::vec3 objColor = OBJECT_COLOR;
    glUniform3fv(objColor_loc, 1, (float*)&objColor);
}
