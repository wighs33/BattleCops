#include "stdafx.h"
#include "Light.h"

void Light::Init() {
    glm::vec3 lightAmbient = light_ambient;
    glUniform3fv(lightAmbient_loc, 1, (float*)&lightAmbient);

    glm::vec3 lightPos = light_pos;
    glUniform3fv(lightPos_loc, 1, (float*)&lightPos);

    glm::vec3 lightColor = light_color;
    glUniform3fv(lightColor_loc, 1, (float*)&lightColor);
}
