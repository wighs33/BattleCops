#pragma once

enum Cube_Face {
    WHOLE = -1,
    FLOOR = 1,
    FRONT = 2
};

class Shape {
public:
    virtual void Color() {}
    virtual void Set_Colors(vector<glm::vec3> colors) { colors_ = colors; }

    bool  loadOBJ(const char* path);
    virtual bool Init_VAO(GLuint shader_program_ID);

    GLuint pos_VBO_ID, color_VBO_ID;
    GLuint normal_VBO_ID, uv_VBO_ID;
    GLuint VAO_ID;

    vector<glm::vec3> colors_;
    const char* path_;

    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

    int texturing_face = -1;
};