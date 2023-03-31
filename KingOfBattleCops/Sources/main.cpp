#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction1(int value);
GLvoid Mouse(int button, int state, int x, int y);

GLfloat mx = 0.0f;
GLfloat my = 0.0f;

GLuint shader_program_ID;

bool isTimer1On = false;
bool isTimer2On = false;
bool isTimer3On = false;

bool isAllStop = false;

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
    //--- ����� ���� ����
    glClearColor(background_color.r, background_color.g, background_color.b, 1.0f); // �������� ����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glUseProgram(shader_program_ID);


    glutSwapBuffers();
    isAllStop = false;

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


    glutDisplayFunc(drawScene); // ��� �Լ��� ����
    glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMainLoop(); // �̺�Ʈ ó�� ���� 
}