#pragma once

#define OBJECT_COLOR	 glm::vec3(1.0, 1.0, 1.0)
#define LIGHT_AMBIENT	glm::vec3(0.1, 0.1, 0.1)
#define LIGHT_POS		glm::vec3(3.0, 3.0, 0.0)
#define LIGHT_COLOR		glm::vec3(1.0, 1.0, 1.0)

class Light
{
public:
    void Init();

    GLuint lightAmbient_loc;
    GLuint lightPos_loc;
    GLuint lightColor_loc;
    GLuint objColor_loc;

	bool isLightRed = false;
	bool isLightGreen = false;
	bool isLightBlue = false;

    double yRotate_light = 0.0;
    float yRotate_lightbox = 0.0f;

    bool isPlus_light = true;
};

