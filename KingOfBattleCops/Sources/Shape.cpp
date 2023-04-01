#include "stdafx.h"
#include "Shape.h"

bool Shape::loadOBJ(const char* path)
{
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    vertexIndices.clear();
    uvIndices.clear();
    normalIndices.clear();
    vertices.clear();
    uvs.clear();
    normals.clear();

    ifstream in(path);
    if (!in) {
        cerr << path << "파일 못찾음";
        exit(1);
    }

    //vector<char> lineHeader(istream_iterator<char>{in}, {});

    while (in) {
        string lineHeader;
        in >> lineHeader;
        if (lineHeader == "v") {
            glm::vec3 vertex;
            in >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        else if (lineHeader == "vt") {
            glm::vec2 uv;
            in >> uv.x >> uv.y;
            temp_uvs.push_back(uv);
        }
        else if (lineHeader == "vn") {
            glm::vec3 normal;
            in >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (lineHeader == "f") {
            char a;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

            for (int i = 0; i < 3; i++)
            {
                in >> vertexIndex[i] >> a >> uvIndex[i] >> a >> normalIndex[i];
                vertexIndices.push_back(vertexIndex[i] - 1);
                uvIndices.push_back(uvIndex[i] - 1);
                normalIndices.push_back(normalIndex[i] - 1);
            }
        }
    }

    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex];
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < uvIndices.size(); i++) {
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 uv = temp_uvs[uvIndex];
        uvs.push_back(uv);
    }

    for (unsigned int i = 0; i < normalIndices.size(); i++) {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[normalIndex];
        normals.push_back(normal);
    }

    return true;
}

bool Shape::Init_VAO(GLuint shader_program_ID)
{
    loadOBJ(path_);

    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);

    //Vertex Buffer Object(VBO)를 생성하여 vertex 데이터를 복사한다.
    //위치
    glGenBuffers(1, &pos_VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, pos_VBO_ID);
	if (texturing_face == -1)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3)/6, &vertices[0] + texturing_face * 6, GL_STATIC_DRAW);

    GLint positionAttribute = glGetAttribLocation(shader_program_ID, "in_position");
    if (positionAttribute == -1) {
        cerr << "position 속성 설정 실패" << endl;
        return false;
    }
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);

    //노말
	glGenBuffers(1, &normal_VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, normal_VBO_ID);
	if (texturing_face == -1)
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3)/6, &normals[0] + texturing_face * 6, GL_STATIC_DRAW);

	GLint normalAttribute = glGetAttribLocation(shader_program_ID, "in_normal");
	if (normalAttribute == -1) {
		cerr << "normal 속성 설정 실패" << endl;
		return false;
	}
	glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normalAttribute);

	//uv
	glGenBuffers(1, &uv_VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, uv_VBO_ID);
	if (texturing_face == -1)
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2)/6, &uvs[0] + texturing_face * 6, GL_STATIC_DRAW);

    GLint uvAttribute = glGetAttribLocation(shader_program_ID, "in_uv");
    if (uvAttribute == -1) {
        cerr << " uv 속성 설정 실패" << endl;
        return false;
    }
    glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uvAttribute);

    //칼라
    //glGenBuffers(1, &color_VBO_ID);
    //glBindBuffer(GL_ARRAY_BUFFER, color_VBO_ID);
    //glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(glm::vec3), &colors_[0], GL_STATIC_DRAW);

    //GLint colorAttribute = glGetAttribLocation(shader_program_ID, "vColor");
    //if (colorAttribute == -1) {
    //    cerr << "color 속성 설정 실패" << endl;
    //    return false;
    //}
    //glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(colorAttribute);

    glBindVertexArray(0);

    return true;
}
