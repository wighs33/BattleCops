#pragma once

class Light
{
public:
    void Init();

    void Set_LightAmbient_Loc(GLuint val) { lightAmbient_loc = val; }
    void Set_LightPos_Loc(GLuint val) { lightPos_loc = val; }
    void Set_LightColor_Loc(GLuint val) { lightColor_loc = val; }
    void Set_ObjColor_Loc(GLuint val) { objColor_loc = val; }

    glm::vec3 object_color = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 light_ambient = glm::vec3(0.5, 0.5, 0.5);
    glm::vec3 light_pos = glm::vec3(3.0, 3.0, 0.0);
    glm::vec3 light_color = glm::vec3(1.0, 1.0, 1.0);

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

