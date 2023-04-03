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
Sky sky;
Field field;
Lobby lobby;
Lobby_Floor lobby_floor;
Door door;
Desk desk;

enum Texture_Image{
    SKY,
    GRASS,
    WALL,
    WOOD,
    WOODFLOOR
};

class Texture {
public:
    Texture(){
        images[0] = stbi_load("Resources/sky.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[1] = stbi_load("Resources/grass.png", &tex_w, &tex_h, &numberOfChannel, 3);
        images[2] = stbi_load("Resources/wall.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[3] = stbi_load("Resources/wood.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[4] = stbi_load("Resources/lobbyfloortex.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
    }

    ~Texture() {
        for (size_t i = 0; i < MAX_IMAGES; i++)
        {
            stbi_image_free(images[i]);
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

    void Coat(int image_type) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, tex_w, tex_h, 0, GL_RGB, GL_UNSIGNED_BYTE, images[image_type]); //---�ؽ�ó �̹��� ����
    }

    int tex_w = 200;
    int tex_h = 200;

    int numberOfChannel = 1;

    static const int MAX_IMAGES = 5;
    unsigned char* images[MAX_IMAGES];

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

    tex.Coat(SKY);
    sky.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(GRASS);
    field.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(WALL);
    lobby.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(WOODFLOOR);
    lobby_floor.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(WOOD);
    door.Init_And_Render(shader_manager.Get_Model_Loc());
    desk.Init_And_Render(shader_manager.Get_Model_Loc());


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

    bool test = true;
    test &= sphere.Init_VAO(shader_program_ID);
    test &= sky.Init_VAO(shader_program_ID);
    test &= field.Init_VAO(shader_program_ID);
    test &= lobby.Init_VAO(shader_program_ID);
    test &= lobby_floor.Init_VAO(shader_program_ID);
    test &= door.Init_VAO(shader_program_ID);
    test &= desk.Init_VAO(shader_program_ID);

    if (!test) {
        cerr << "Error: ������Ʈ ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    glutDisplayFunc(drawScene); // ��� �Լ��� ����
    glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMainLoop(); // �̺�Ʈ ó�� ���� 
}