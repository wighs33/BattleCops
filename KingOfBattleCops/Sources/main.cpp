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

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
    //--- 변경된 배경색 설정
    glClearColor(background_color.r, background_color.g, background_color.b, 1.0f); // 바탕색을 변경
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glUseProgram(shader_program_ID);


    glutSwapBuffers();
    isAllStop = false;

    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
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
    glutPostRedisplay(); //--- 배경색이 바뀔때마다 출력 콜백함수를 호출하여 화면을 refresh 한다
}

//앞면이 올라가고 로봇이 팔다리를 흔듦
GLvoid TimerFunction1(int value)
{
    glutPostRedisplay(); // 화면 재 출력
    if (isTimer1On)
        glutTimerFunc(100, TimerFunction1, 1);
}

GLvoid Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{   //--- 윈도우 생성하기
    glutInit(&argc, argv); // glut 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
    glutInitWindowPosition(WIN_X, WIN_Y); // 윈도우의 위치 지정
    glutInitWindowSize((int)WIN_W, (int)WIN_H); // 윈도우의 크기 지정
    glutCreateWindow("Example1"); // 윈도우 생성 (윈도우 이름)

    //--- GLEW 초기화하기
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) // glew 초기화
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    stbi_set_flip_vertically_on_load(true); //--- 이미지가 거꾸로 읽힌다면 추가


    glutDisplayFunc(drawScene); // 출력 함수의 지정
    glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMainLoop(); // 이벤트 처리 시작 
}