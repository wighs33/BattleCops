#include "stdafx.h"
#include "ShaderManager.h"

char* ShaderManager::File_To_Buf(const char* file)
{
    ifstream in(file, ios_base::binary);

    if (!in) {
        cerr << file << "파일 못찾음";
        exit(1);
    }

    in.seekg(0, ios_base::end);
    long len = (long)in.tellg();
    char* buf = new char[len + 1];
    in.seekg(0, ios_base::beg);

    int cnt = -1;
    while (in >> noskipws >> buf[++cnt]) {}
    buf[len] = 0;

    return buf;
}

bool ShaderManager::Init_Program()
{
    const GLchar* vertexShaderSource = File_To_Buf("Resources/vertex.glsl");
    const GLchar* fragmentShaderSource = File_To_Buf("Resources/fragment.glsl");


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
        glDeleteShader(vertexShader);
        return false;
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;

        return false;
    }


    shader_program_ID = glCreateProgram();

    glAttachShader(shader_program_ID, vertexShader);
    glAttachShader(shader_program_ID, fragmentShader);

    glLinkProgram(shader_program_ID);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader_program_ID, 512, NULL, errorLog);
        cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;
        return false;
    }
    glUseProgram(shader_program_ID);

    return true;
}

void ShaderManager::Mapping()
{
    model_loc = glGetUniformLocation(shader_program_ID, "g_model");
    view_loc = glGetUniformLocation(shader_program_ID, "g_view");
    proj_loc = glGetUniformLocation(shader_program_ID, "g_projection");

    lightAmbi_loc = glGetUniformLocation(shader_program_ID, "g_lightAmbient");
    lightPos_loc = glGetUniformLocation(shader_program_ID, "g_lightPos");
    lightColor_loc = glGetUniformLocation(shader_program_ID, "g_lightColor");
    objColor_loc = glGetUniformLocation(shader_program_ID, "g_objectColor");
    cameraPos_loc = glGetUniformLocation(shader_program_ID, "g_cameraPos");

    texture_loc = glGetUniformLocation(shader_program_ID, "outColor");
    glUniform1i(texture_loc, 0); //--- 샘플러를 0번 유닛으로 설정
}
