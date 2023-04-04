#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Cube.h"
#include "Robot.h"

GLfloat mx = 0.0f;
GLfloat my = 0.0f;

GLuint shader_program_ID;

bool is_move_timer_on = false;
bool is_update_timer_on = true;
bool is_start_check_timer_on = true;

bool isAllStop = false;

enum gamestatelist { START, LOBBY };
int gamestate = LOBBY;

class Texture;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid SpecialKeyPress(int key, int x, int y);
GLvoid SpecialKeyUp(int key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);

GLvoid MoveTimer(int value);
GLvoid GameUpdateTimer(int value);
GLvoid GameStartCheckTimer(int value);
GLvoid stoneCreateTimer(int value);
GLvoid missileCreateTimer(int value);
GLvoid stoneThrowTimer(int value);
GLvoid comStoneThrowTimer(int value);
GLvoid changeDirTimer(int value);
GLvoid comMoveTimer(int value);

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
Robot player_robot(20.0f, 0.0f);

enum Texture_Image{
    SKY,
    GRASS,
    WALL,
    WOOD,
    WOODFLOOR,
    NONE
};

class Texture {
public:
    Texture(){
        images[0] = stbi_load("Resources/sky.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[1] = stbi_load("Resources/grass.png", &tex_w, &tex_h, &numberOfChannel, 3);
        images[2] = stbi_load("Resources/wall.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[3] = stbi_load("Resources/wood.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[4] = stbi_load("Resources/lobbyfloortex.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[5] = nullptr;
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

    static const int MAX_IMAGES = 6;
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

    for (size_t i = 0; i < player_robot.MAX_BODIES; i++)
        player_robot.bodies[i].Set_Colors(glm::vec3(1.0, 0.0, 0.0), shader_manager.Get_ObjColor_Loc());
    player_robot.Init_And_Render(shader_manager.Get_Model_Loc());


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

GLvoid SpecialKeyPress(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        player_robot.dir = DIR_FRONT;
        if (player_robot.z_move > -14.8)
            player_robot.z_move -= 0.1;
        player_robot.y_rotate = 180.0f;

        if (!is_move_timer_on)
            glutTimerFunc(100, MoveTimer, 1);
        is_move_timer_on = true;
        break;
    case GLUT_KEY_DOWN:
        player_robot.dir = DIR_BACK;
        if (gamestate == LOBBY && player_robot.z_move < 10.0)
            player_robot.z_move += 0.1;
        else if (gamestate == START && player_robot.z_move < 14.8)
            player_robot.z_move += 0.1;
        player_robot.y_rotate = 0.0f;

        if (!is_move_timer_on)
            glutTimerFunc(100, MoveTimer, 1);
        is_move_timer_on = true;
        break;
    case GLUT_KEY_LEFT:
        player_robot.dir = DIR_LEFT;
        //���� �浹üũ, ���� ���
        if ((player_robot.z_move > 0.5 || player_robot.z_move < -0.5) && player_robot.x_move < 15.2);
        else if(gamestate == LOBBY)
            player_robot.x_move -= 0.1;

        if (gamestate == START && player_robot.x_move > -14.8)
            player_robot.x_move -= 0.1;
        player_robot.y_rotate = -90.0f;

        if (!is_move_timer_on)
            glutTimerFunc(100, MoveTimer, 1);
        is_move_timer_on = true;
        break;
    case GLUT_KEY_RIGHT:
        player_robot.dir = DIR_RIGHT;
        if (gamestate == LOBBY && player_robot.x_move < 24.8)
            player_robot.x_move += 0.1;
        else if (gamestate == START && player_robot.x_move < 14.8)
            player_robot.x_move += 0.1;
        player_robot.y_rotate = 90.0f;

        if (!is_move_timer_on)
            glutTimerFunc(100, MoveTimer, 1);
        is_move_timer_on = true;
        break;
    }
    glutPostRedisplay();
}

GLvoid SpecialKeyUp(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        is_move_timer_on = false;
        break;
    case GLUT_KEY_DOWN:
        is_move_timer_on = false;
        break;
    case GLUT_KEY_LEFT:
        is_move_timer_on = false;
        break;
    case GLUT_KEY_RIGHT:
        is_move_timer_on = false;
        break;
    }
    glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'r':
        break;
    }
    glutPostRedisplay(); //--- ������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}

GLvoid GameUpdateTimer(int value) 
{
    if (player_robot.x_move < 14.8)
        gamestate = START;

    glutPostRedisplay(); // ȭ�� �� ���
    if (is_update_timer_on)
        glutTimerFunc(100, GameUpdateTimer, 1);
}

GLvoid GameStartCheckTimer(int value)
{
    if (gamestate == START) {
		cam.Set_CameraPos(glm::vec3(0.0, 22.0, 19.0));
		player_robot.x_move = 8.0;
		player_robot.z_move = 8.0;
		//glutTimerFunc(1000, stoneCreateTimer, 1);
		//glutTimerFunc(1000, missileCreateTimer, 1);
		//glutTimerFunc(100, comMoveTimer, 1);
		//glutTimerFunc(3000, changeDirTimer, 1);
		//robot1.comDir = BACK;
		//robot2.comDir = BACK;
		//robot3.comDir = BACK;
		//comRobot.push_back(robot1);
		//comRobot.push_back(robot2);
		//comRobot.push_back(robot3);
		is_start_check_timer_on = false;
    }

    glutPostRedisplay(); // ȭ�� �� ���
    if (is_start_check_timer_on)
        glutTimerFunc(100, GameStartCheckTimer, 1);
}

//�κ��� �ȴٸ��� ���
GLvoid MoveTimer(int value)
{
    if (player_robot.x_rotate > 30.0f or player_robot.x_rotate < -30.0f)
        player_robot.is_forward ^= 1;

    if (player_robot.is_forward)
        player_robot.x_rotate += player_robot.rotate_rate;
    else
        player_robot.x_rotate -= player_robot.rotate_rate;

    glutPostRedisplay(); // ȭ�� �� ���
    if (is_move_timer_on)
        glutTimerFunc(100, MoveTimer, 1);
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

    for (size_t i = 0; i < player_robot.MAX_BODIES; i++)
    {
        player_robot.bodies[i].is_textured = false;
        test &= player_robot.bodies[i].Init_VAO(shader_program_ID);
    }

    if (!test) {
        cerr << "Error: ������Ʈ ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    glutDisplayFunc(drawScene); // ��� �Լ��� ����
    glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyPress);
    glutSpecialUpFunc(SpecialKeyUp);
    glutMouseFunc(Mouse);
    glutTimerFunc(100, GameUpdateTimer, 1);
    glutTimerFunc(100, GameStartCheckTimer, 1);
    glutMainLoop(); // �̺�Ʈ ó�� ���� 
}