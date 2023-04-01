#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Cube.h"

GLfloat mx = 0.0f;
GLfloat my = 0.0f;

GLuint shader_program_ID;

bool isTimer1On = false;
bool isTimer2On = false;
bool isTimer3On = false;

bool isAllStop = false;

class Texture;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction1(int value);
GLvoid Mouse(int button, int state, int x, int y);

ShaderManager shader_manager;
Camera cam;
Light light;
Sphere sphere;
Cube cube;

class Texture {
public:
    Texture() : skydata(stbi_load("Resources/sky.jpg", &tex_w, &tex_h, &numberOfChannel, 3)) {
        data[0] = stbi_load("Resources/tex0.png", &tex_w, &tex_h, &numberOfChannel, 3);
        data[1] = stbi_load("Resources/tex1.png", &tex_w, &tex_h, &numberOfChannel, 3);
        data[2] = stbi_load("Resources/tex2.png", &tex_w, &tex_h, &numberOfChannel, 3);
        data[3] = stbi_load("Resources/tex3.png", &tex_w, &tex_h, &numberOfChannel, 3);
        data[4] = stbi_load("Resources/tex4.png", &tex_w, &tex_h, &numberOfChannel, 3);
        data[5] = stbi_load("Resources/tex5.png", &tex_w, &tex_h, &numberOfChannel, 3);
    }

    ~Texture() {
        stbi_image_free(skydata);

        for (size_t i = 0; i < 6; i++)
        {
            stbi_image_free(data[i]);
        }
    }

    void Init() {
        glGenTextures(1, &texture_id); //--- �ؽ�ó ����
        glBindTexture(GL_TEXTURE_2D, texture_id); //--- �ؽ�ó ���ε�
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    int tex_w = 200;
    int tex_h = 200;

    int numberOfChannel = 1;

    unsigned char* skydata;
    unsigned char* data[6];

    unsigned int texture_id;
};

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
    //--- ����� ���� ����
    glClearColor(background_color.r, background_color.g, background_color.b, 1.0f); // �������� ����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    Texture tex;
    tex.Init();

    glUseProgram(shader_program_ID);

    shader_manager.Mapping();

    light.Set_LightAmbient_Loc(shader_manager.Get_LightAmbient_Loc());
    light.Set_LightPos_Loc(shader_manager.Get_LightPos_Loc());
    light.Set_LightColor_Loc(shader_manager.Get_LightColor_Loc());
    light.Set_ObjColor_Loc(shader_manager.Get_ObjColor_Loc());
    light.Init();

    cam.Set_View_Loc(shader_manager.Get_View_Loc());
    cam.Set_CameraPos_Loc(shader_manager.Get_CameraPos_Loc());
    cam.Set_Proj_Loc(shader_manager.Get_Proj_Loc());
    cam.Init();

    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.tex_w, tex.tex_h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.skydata); //---�ؽ�ó �̹��� ����
    cube.Init_And_Render(shader_manager.Get_Model_Loc());

    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.tex_w, tex.tex_h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.data[3]); //---�ؽ�ó �̹��� ����
    sphere.Init_And_Render(shader_manager.Get_Model_Loc());


    isAllStop = false;
    glutSwapBuffers();
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
    WIN_W = (float)w;
    WIN_H = (float)h;
    glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'r':    case 'R':
        if (!isTimer1On)
            glutTimerFunc(100, TimerFunction1, 1);
        isTimer1On = true;
        break;
    }
    glutPostRedisplay(); //--- ������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}

//�ո��� �ö󰡰� �κ��� �ȴٸ��� ���
GLvoid TimerFunction1(int value)
{
    glutPostRedisplay(); // ȭ�� �� ���
    if (isTimer1On)
        glutTimerFunc(100, TimerFunction1, 1);
}

GLvoid Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{   //--- ������ �����ϱ�
    glutInit(&argc, argv); // glut �ʱ�ȭ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
    glutInitWindowPosition(WIN_X, WIN_Y); // �������� ��ġ ����
    glutInitWindowSize((int)WIN_W, (int)WIN_H); // �������� ũ�� ����
    glutCreateWindow("Example1"); // ������ ���� (������ �̸�)

    //--- GLEW �ʱ�ȭ�ϱ�
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    stbi_set_flip_vertically_on_load(true); //--- �̹����� �Ųٷ� �����ٸ� �߰�

    if (!shader_manager.Init_Program()) {
        cerr << "Error: Shader Program ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }
    shader_program_ID = shader_manager.shader_program_ID;

    if (!sphere.Init_VAO(shader_program_ID)) {
        cerr << "Error: �� ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    cube.texturing_face = 2;
    if (!cube.Init_VAO(shader_program_ID)) {
        cerr << "Error: �� ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }


    glutDisplayFunc(drawScene); // ��� �Լ��� ����
    glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMainLoop(); // �̺�Ʈ ó�� ���� 
}