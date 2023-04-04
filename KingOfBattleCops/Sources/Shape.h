#pragma once

enum Cube_Face {
    CUBE_WHOLE = -1,
    CUBE_FLOOR = 1,
    CUBE_FRONT = 2
};

class Shape {
public:
    virtual void Set_Colors(glm::vec3 colors, GLuint objColor_loc) {
        colors_ = colors; 
        glUniform3fv(objColor_loc, 1, (float*)&colors_);
    }

    bool  loadOBJ(const char* path);
    virtual bool Init_VAO(GLuint shader_program_ID);

    virtual void Init_And_Render(int model) {}

    GLuint pos_VBO_ID, color_VBO_ID;
    GLuint normal_VBO_ID, uv_VBO_ID;
    GLuint VAO_ID;

    glm::vec3 colors_;
    const char* path_;

    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

    int texturing_face = -1;
    bool is_textured = true;
};