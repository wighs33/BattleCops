#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Cube.h"
#include "Robot.h"
#include "Missile.h"

GLfloat mx = 0.0f;
GLfloat my = 0.0f;

GLuint shader_program_ID;

bool is_move_timer_on = false;
bool is_update_timer_on = true;
bool is_start_check_timer_on = true;
bool is_ai_move_timer_on = false;
bool is_random_dir_timer_on = false;
bool is_stone_create_timer_on = false;
bool is_missile_create_timer_on = false;
bool is_stone_throw_timer_on = false;
bool is_missile_throw_timer_on = false;

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

GLvoid WorkMotionTimer(int value);
GLvoid GameUpdateTimer(int value);
GLvoid GameStartCheckTimer(int value);
GLvoid AiMoveTimer(int value);
GLvoid RandomDirTimer(int value);
GLvoid StoneCreateTimer(int value);
GLvoid MissileCreateTimer(int value);
GLvoid StoneThrowTimer(int value);
GLvoid MissileThrowTimer(int value);

ShaderManager shader_manager;
Camera cam;
Light light;
Sphere sphere;
Sky sky;
Field field(glm::vec3(30.0f, 0.0f, 30.0f), 0.5f);
Field field2(glm::vec3(80.0f, 0.0f, 50.0f), 0.6f);
Lobby lobby;
Lobby_Floor lobby_floor;
Door door;
Desk desk;
Robot player_robot(20.0f, 0.0f);

vector<Robot> ai_robots;
vector<Stone> stoneList;
vector<Missile> missileList;
deque<int> indice_of_throwed_stones;
deque<int> indice_of_throwed_missiles;
deque<int> indice_of_stone_throwed_by_ai;

class Texture {
public:
    Texture(){
        images[0] = stbi_load("Resources/sky.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[1] = stbi_load("Resources/grass.png", &tex_w, &tex_h, &numberOfChannel, 3);
        images[2] = stbi_load("Resources/wall.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[3] = stbi_load("Resources/wood.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[4] = stbi_load("Resources/lobbyfloortex.jpg", &tex_w, &tex_h, &numberOfChannel, 3);
        images[5] = stbi_load("Resources/stone.png", &tex_w, &tex_h, &numberOfChannel, 3);
        images[6] = stbi_load("Resources/soil.png", &tex_w, &tex_h, &numberOfChannel, 3);
    }

    ~Texture() {
        for (size_t i = 0; i < MAX_IMAGES; i++)
        {
            stbi_image_free(images[i]);
        }
    }

    void Init() {
        glGenTextures(1, &texture_id); //--- 텍스처 생성
        glBindTexture(GL_TEXTURE_2D, texture_id); //--- 텍스처 바인딩
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void Coat(GLuint objColor_loc, int image_type){
        glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
        glUniform3fv(objColor_loc, 1, (float*)&color);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, tex_w, tex_h, 0, GL_RGB, GL_UNSIGNED_BYTE, images[image_type]); //---텍스처 이미지 정의
    }

    int tex_w = 200;
    int tex_h = 200;

    int numberOfChannel = 1;

    static const int MAX_IMAGES = 7;
    unsigned char* images[MAX_IMAGES];

    unsigned int texture_id;
};

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
    //--- 변경된 배경색 설정
    glClearColor(background_color.r, background_color.g, background_color.b, 1.0f); // 바탕색을 변경
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
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
    light.Init();

    cam.Set_View_Loc(shader_manager.Get_View_Loc());
    cam.Set_CameraPos_Loc(shader_manager.Get_CameraPos_Loc());
    cam.Set_Proj_Loc(shader_manager.Get_Proj_Loc());
    cam.Init();

    tex.Coat(shader_manager.Get_ObjColor_Loc(), SKY);
    sky.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(shader_manager.Get_ObjColor_Loc(), GRASS);
    field.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(shader_manager.Get_ObjColor_Loc(), SOIL);
    field2.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(shader_manager.Get_ObjColor_Loc(), WALL);
    lobby.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(shader_manager.Get_ObjColor_Loc(), WOODFLOOR);
    lobby_floor.Init_And_Render(shader_manager.Get_Model_Loc());

    tex.Coat(shader_manager.Get_ObjColor_Loc(), WOOD);
    door.Init_And_Render(shader_manager.Get_Model_Loc());
    desk.Init_And_Render(shader_manager.Get_Model_Loc());

    for (size_t i = 0; i < Robot::MAX_BODIES; i++)
        player_robot.bodies[i].Set_Colors(glm::vec3(1.0, 0.0, 0.0), shader_manager.Get_ObjColor_Loc());
    player_robot.Init_And_Render(shader_manager.Get_Model_Loc());

    glm::vec3 temp_colors[3] = { glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0) };

	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < Robot::MAX_BODIES; j++)
		{
			ai_robots[i].bodies[j].Set_Colors(temp_colors[i], shader_manager.Get_ObjColor_Loc());
			ai_robots[i].Init_And_Render(shader_manager.Get_Model_Loc());
		}

    tex.Coat(shader_manager.Get_ObjColor_Loc(), STONE);
    if (stoneList.size() > 0)
        for (auto stone : stoneList)
            stone.Init_And_Render(shader_manager.Get_Model_Loc());

    if (missileList.size() > 0)
        for (auto missile : missileList)
        {
            missile.Set_Colors(glm::vec3(1.0, 0.0, 0.0), shader_manager.Get_ObjColor_Loc());
            missile.Init_And_Render(shader_manager.Get_Model_Loc());
        }


    isAllStop = false;
    glutSwapBuffers();
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
{
    WIN_W = (float)w;
    WIN_H = (float)h;
    glViewport(0, 0, w, h);
}

GLvoid SpecialKeyPress(int key, int x, int y) {
    if (player_robot.state == DIE) {
        glutPostRedisplay();
        return;
    }

    switch (key) {
    case GLUT_KEY_UP:
        player_robot.dir = DIR_FRONT;
        if (player_robot.pos.z > -14.8)
            player_robot.pos.z -= 0.1f;
        player_robot.y_rotate = 180.0f;

        if (!is_move_timer_on)
            glutTimerFunc(100, WorkMotionTimer, 1);
        is_move_timer_on = true;
        break;
    case GLUT_KEY_DOWN:
        player_robot.dir = DIR_BACK;
        if (gamestate == LOBBY && player_robot.pos.z < 10.0)
            player_robot.pos.z += 0.1f;
        else if (gamestate == START && player_robot.pos.z < 14.8)
            player_robot.pos.z += 0.1f;
        player_robot.y_rotate = 0.0f;

        if (!is_move_timer_on)
            glutTimerFunc(100, WorkMotionTimer, 1);
        is_move_timer_on = true;
        break;
    case GLUT_KEY_LEFT:
        player_robot.dir = DIR_LEFT;
        //벽과 충돌체크, 문은 통과
        if ((player_robot.pos.z > 0.5 || player_robot.pos.z < -0.5) && player_robot.pos.x < 15.2);
        else if(gamestate == LOBBY)
            player_robot.pos.x -= 0.1f;

        if (gamestate == START && player_robot.pos.x > -14.8)
            player_robot.pos.x -= 0.1f;
        player_robot.y_rotate = -90.0f;

        if (!is_move_timer_on)
            glutTimerFunc(100, WorkMotionTimer, 1);
        is_move_timer_on = true;
        break;
    case GLUT_KEY_RIGHT:
        player_robot.dir = DIR_RIGHT;
        if (gamestate == LOBBY && player_robot.pos.x < 24.8)
            player_robot.pos.x += 0.1f;
        else if (gamestate == START && player_robot.pos.x < 14.8)
            player_robot.pos.x += 0.1f;
        player_robot.y_rotate = 90.0f;

        if (!is_move_timer_on)
            glutTimerFunc(100, WorkMotionTimer, 1);
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
    if (player_robot.state == DIE) {
        glutPostRedisplay();
        return;
    }

    switch (key) {
    case 'x': case 'X':
        player_robot.state = HOLD;
        break;
    case 'c': case 'C':
        if (player_robot.state == HOLD)
            player_robot.state = THROW;
        break;
    }
    glutPostRedisplay(); //--- 배경색이 바뀔때마다 출력 콜백함수를 호출하여 화면을 refresh 한다
}

GLvoid GameUpdateTimer(int value) 
{
    if (player_robot.pos.x < 14.8)
        gamestate = START;

    if (player_robot.state == HOLD) {
        //돌덩이 리스트에서 잡을 수 있는 돌덩이 탐색하기
        for (size_t i = 0; i < stoneList.size(); ++i) {
            if (player_robot.pos.x > stoneList[i].pos.x - 0.5
                && player_robot.pos.x < stoneList[i].pos.x + 0.5
                && player_robot.pos.z > stoneList[i].pos.z - 0.5
                && player_robot.pos.z < stoneList[i].pos.z + 0.5) {
                player_robot.retained_stone_index = i;
                break;
            }
        }

        for (size_t i = 0; i < missileList.size(); ++i) {
            if (player_robot.retained_stone_index == -1
                &&player_robot.pos.x > missileList[i].pos.x - 0.5
                && player_robot.pos.x < missileList[i].pos.x + 0.5
                && player_robot.pos.z > missileList[i].pos.z - 0.5
                && player_robot.pos.z < missileList[i].pos.z + 0.5) {
                player_robot.retained_missile_index = i;
                break;
            }
        }

        if (player_robot.retained_stone_index == -1 && player_robot.retained_missile_index == -1)
        {
            player_robot.state = IDLE;
        }
        else if(player_robot.retained_stone_index != -1){
            stoneList[player_robot.retained_stone_index].pos.x = player_robot.pos.x;
            stoneList[player_robot.retained_stone_index].pos.y = 1.0f;
            stoneList[player_robot.retained_stone_index].pos.z = player_robot.pos.z;
        }
        else if (player_robot.retained_missile_index != -1) {
                missileList[player_robot.retained_missile_index].pos.x = player_robot.pos.x;
                missileList[player_robot.retained_missile_index].pos.y = 1.0f;
                missileList[player_robot.retained_missile_index].pos.z = player_robot.pos.z;
                missileList[player_robot.retained_missile_index].y_rotate = player_robot.y_rotate;
        }
    }

    if (player_robot.state == THROW) {
        player_robot.state = IDLE;
        //플레이어가 보유한 돌의 인덱스를 컨테이너에 저장하기
        if (player_robot.retained_stone_index != -1)
        {
            indice_of_throwed_stones.push_back(player_robot.retained_stone_index);
            stoneList[player_robot.retained_stone_index].throw_dir = player_robot.dir;
            player_robot.retained_stone_index = -1;
        }
        else if (player_robot.retained_missile_index != -1)
        {
            indice_of_throwed_missiles.push_back(player_robot.retained_missile_index);
            missileList[player_robot.retained_missile_index].throw_dir = player_robot.dir;
            player_robot.retained_missile_index = -1;
        }
    }

    for (auto& bot : ai_robots)
    {
        for (size_t i = 0; i < stoneList.size(); ++i)
        {
            if (i == player_robot.retained_stone_index) continue;
            if (stoneList[i].is_retained) continue;

            if (bot.state == IDLE
                && bot.pos.x > stoneList[i].pos.x - 8.0
                && bot.pos.x < stoneList[i].pos.x + 8.0
                && bot.pos.z > stoneList[i].pos.z - 8.0
                && bot.pos.z < stoneList[i].pos.z + 8.0) {
                bot.state = MOVE_TO_STONE;
                bot.index_of_stone_to_get = i;
                break;
            }
        }
    }

    for(auto& bot : ai_robots) {
        if (bot.state == HOLD)
        {
            stoneList[bot.retained_stone_index].pos.x = bot.pos.x;
            stoneList[bot.retained_stone_index].pos.y = 1.0f;
            stoneList[bot.retained_stone_index].pos.z = bot.pos.z;

            if (player_robot.pos.x > bot.pos.x - 6.0
                && player_robot.pos.x < bot.pos.x + 6.0
                && player_robot.pos.z > bot.pos.z - 6.0
                && player_robot.pos.z < bot.pos.z + 6.0)
            {
                bot.state = IDLE;

                indice_of_stone_throwed_by_ai.push_back(bot.retained_stone_index);

                float x = player_robot.pos.x - stoneList[bot.retained_stone_index].pos.x;
                float z = player_robot.pos.z - stoneList[bot.retained_stone_index].pos.z;

				stoneList[bot.retained_stone_index].throw_rate = glm::vec2(x / 5 / sqrt(x*x + z*z), z / 5 / sqrt(x * x + z * z));
                bot.retained_stone_index = -1;
            }
        }
    }

    glutPostRedisplay(); // 화면 재 출력
    if (is_update_timer_on)
        glutTimerFunc(100, GameUpdateTimer, 1);
}

GLvoid GameStartCheckTimer(int value)
{
    if (gamestate == START) {
		cam.Set_CameraPos(glm::vec3(0.0, 22.0, 19.0));
		player_robot.pos.x = 8.0;
		player_robot.pos.z = 8.0;

        is_ai_move_timer_on = true;
        glutTimerFunc(100, AiMoveTimer, 1);
        is_random_dir_timer_on = true;
        glutTimerFunc(3000, RandomDirTimer, 1);
        is_stone_create_timer_on = true;
		glutTimerFunc(1000, StoneCreateTimer, 1);
        is_missile_create_timer_on = true;
		glutTimerFunc(3000, MissileCreateTimer, 1);
        is_stone_throw_timer_on = true;
        glutTimerFunc(10, StoneThrowTimer, 1);
        is_missile_throw_timer_on = true;
        glutTimerFunc(3, MissileThrowTimer, 1);

        //한 번만 실행하고 끄기
		is_start_check_timer_on = false;
    }

    glutPostRedisplay(); // 화면 재 출력
    if (is_start_check_timer_on)
        glutTimerFunc(100, GameStartCheckTimer, 1);
}

//로봇이 팔다리를 흔듦
GLvoid WorkMotionTimer(int value)
{
    if (player_robot.x_rotate > 30.0f or player_robot.x_rotate < -30.0f)
        player_robot.is_forward ^= 1;

    if (player_robot.is_forward)
        player_robot.x_rotate += player_robot.rotate_rate;
    else
        player_robot.x_rotate -= player_robot.rotate_rate;

    glutPostRedisplay(); // 화면 재 출력
    if (is_move_timer_on)
        glutTimerFunc(100, WorkMotionTimer, 1);
}

GLvoid AiMoveTimer(int value)
{
    for (auto& bot : ai_robots)
    {
        if (bot.state == DIE) continue;

        if (bot.x_rotate > 30.0f or bot.x_rotate < -30.0f)
            bot.is_forward ^= 1;

        if (bot.is_forward)
            bot.x_rotate += bot.rotate_rate;
        else
            bot.x_rotate -= bot.rotate_rate;
    }

    for (auto& bot : ai_robots)
    {
        if (bot.state != IDLE && bot.state != HOLD) continue;

		if (bot.dir == DIR_FRONT) {
            if (bot.pos.z < -14.8)
            {
                bot.dir = DIR_BACK;
                break;
            }

            bot.y_rotate = 180.0f;
			bot.pos.z -= 0.1f;
		}
		else if (bot.dir == DIR_BACK) {
            if (bot.pos.z > 14.8)
            {
                bot.dir = DIR_FRONT;
                break;
            }

            bot.y_rotate = 0.0f;
            bot.pos.z += 0.1f;
		}
		else if (bot.dir == DIR_LEFT) {
            if (bot.pos.x < -14.8)
            {
                bot.dir = DIR_RIGHT;
                break;
            }

            bot.y_rotate = -90.0f;
            bot.pos.x -= 0.1f;
		}
		else if (bot.dir == DIR_RIGHT) {
            if (bot.pos.x > 14.8)
            {
                bot.dir = DIR_LEFT;
                break;
            }

            bot.y_rotate = 90.0f;
            bot.pos.x += 0.1f;
		}
    }

    for (auto& bot : ai_robots)
    {
        if (bot.state != MOVE_TO_STONE) continue;
        if (stoneList[bot.index_of_stone_to_get].is_retained) {
            bot.state = IDLE;
            bot.is_finish_to_move_x = false;
            bot.index_of_stone_to_get = -1;
            continue;
        }

        if (bot.pos.x > stoneList[bot.index_of_stone_to_get].pos.x - 0.5
            && bot.pos.x < stoneList[bot.index_of_stone_to_get].pos.x + 0.5) {
            bot.is_finish_to_move_x = true;
        }
        else {
            if (bot.pos.x < stoneList[bot.index_of_stone_to_get].pos.x)
            {
                bot.y_rotate = 90.0f;
                bot.pos.x += 0.1f;
            }
            else {
                bot.y_rotate = -90.0f;
                bot.pos.x -= 0.1f;
            }
        }

        if (bot.pos.z > stoneList[bot.index_of_stone_to_get].pos.z - 0.5
            && bot.pos.z < stoneList[bot.index_of_stone_to_get].pos.z + 0.5) {
            bot.state = HOLD;
            stoneList[bot.index_of_stone_to_get].is_retained = true;
            bot.is_finish_to_move_x = false;
            bot.retained_stone_index = bot.index_of_stone_to_get;
            bot.index_of_stone_to_get = -1;
        }
        else if(bot.is_finish_to_move_x){
            if (bot.pos.z < stoneList[bot.index_of_stone_to_get].pos.z) {
                bot.y_rotate = 0.0f;
                bot.pos.z += 0.1f;
            }
            else {
                bot.y_rotate = 180.0f;
                bot.pos.z -= 0.1f;
            }
        }
    }

    glutPostRedisplay(); // 화면 재 출력
    if (is_ai_move_timer_on)
        glutTimerFunc(100, AiMoveTimer, 1);
}

GLvoid RandomDirTimer(int value)
{
    for (auto& bot : ai_robots) {
        if (bot.state != IDLE && bot.state != HOLD) continue;
        bot.dir = dirDist(eng);
    }

	glutPostRedisplay(); // 화면 재 출력
	if (is_random_dir_timer_on)
		glutTimerFunc(3000, RandomDirTimer, 1);
}

GLvoid StoneCreateTimer(int value)
{
    if (stoneList.size() < 30)
    {
        Stone stone(posDist(eng), posDist(eng));
        stone.Init_VAO(shader_program_ID);

        stoneList.push_back(stone);
    }

    glutPostRedisplay(); // 화면 재 출력
    if (is_stone_create_timer_on)
        glutTimerFunc(2000, StoneCreateTimer, 1);
}

GLvoid MissileCreateTimer(int value)
{
    if (missileList.size() < 15)
    {
        Missile missile(posDist(eng), posDist(eng));

        missile.y_rotate = missileDir(eng);
        missile.is_textured = false;
        missile.Init_VAO(shader_program_ID);

        missileList.push_back(missile);
    }

    glutPostRedisplay(); // 화면 재 출력
    if (is_missile_create_timer_on)
        glutTimerFunc(8000, MissileCreateTimer, 1);
}

GLvoid StoneThrowTimer(int value)
{
    for (auto i : indice_of_throwed_stones)
    {
        auto& temp_stone = stoneList[i];

        temp_stone.pos.y += 0.1f - 0.01f * ++temp_stone.throw_time;

        if (temp_stone.pos.y < 0.0f)
        {
            temp_stone.throw_time = 0;
            temp_stone.throw_dir = DIR_STOP;
            indice_of_throwed_stones.pop_front();
        }

        if (temp_stone.throw_dir == DIR_FRONT)
        {
            temp_stone.pos.z -= 0.2f;
        }
        else if (temp_stone.throw_dir == DIR_BACK)
        {
            temp_stone.pos.z += 0.2f;
        }
        else if (temp_stone.throw_dir == DIR_LEFT)
        {
            temp_stone.pos.x -= 0.2f;
        }
        else if (temp_stone.throw_dir == DIR_RIGHT)
        {
            temp_stone.pos.x += 0.2f;
        }

        for (auto& bot : ai_robots)
        {
            if (bot.pos.x > temp_stone.pos.x - 0.5
                && bot.pos.x < temp_stone.pos.x + 0.5
                && bot.pos.z > temp_stone.pos.z - 0.5
                && bot.pos.z < temp_stone.pos.z + 0.5) {
                bot.state = DIE;
                break;
            }
        }
    }

    for (auto i : indice_of_stone_throwed_by_ai)
    {
        auto& temp_stone = stoneList[i];

        temp_stone.pos.y += 0.1f - 0.01f * ++temp_stone.throw_time;

        if (temp_stone.pos.y < 0.0f)
        {
            temp_stone.throw_time = 0;
			temp_stone.throw_rate = glm::vec2(0.0f, 0.0f);
            indice_of_stone_throwed_by_ai.pop_front();
        }

        temp_stone.pos.x += temp_stone.throw_rate.x;
        temp_stone.pos.z += temp_stone.throw_rate.y;

        if (player_robot.pos.x > temp_stone.pos.x - 0.5
            && player_robot.pos.x < temp_stone.pos.x + 0.5
            && player_robot.pos.z > temp_stone.pos.z - 0.5
            && player_robot.pos.z < temp_stone.pos.z + 0.5) {
            player_robot.state = DIE;
        }
    }

    glutPostRedisplay(); // 화면 재 출력
    if (is_stone_throw_timer_on)
        glutTimerFunc(10, StoneThrowTimer, 1);
}

GLvoid MissileThrowTimer(int value)
{
    for (auto i : indice_of_throwed_missiles)
    {
        auto& temp_missile = missileList[i];

        temp_missile.pos.y += 0.03f - 0.001f * ++temp_missile.throw_time;

        if (temp_missile.pos.y < 0.0f)
        {
            temp_missile.throw_time = 0;
            temp_missile.throw_dir = DIR_STOP;
            indice_of_throwed_missiles.pop_front();
        }

        if (temp_missile.throw_dir == DIR_FRONT)
        {
            temp_missile.pos.z -= 0.2f;
        }
        else if (temp_missile.throw_dir == DIR_BACK)
        {
            temp_missile.pos.z += 0.2f;
        }
        else if (temp_missile.throw_dir == DIR_LEFT)
        {
            temp_missile.pos.x -= 0.2f;
        }
        else if (temp_missile.throw_dir == DIR_RIGHT)
        {
            temp_missile.pos.x += 0.2f;
        }

        for (auto& bot : ai_robots)
        {
            if (bot.pos.x > temp_missile.pos.x - 0.5
                && bot.pos.x < temp_missile.pos.x + 0.5
                && bot.pos.z > temp_missile.pos.z - 0.5
                && bot.pos.z < temp_missile.pos.z + 0.5) {
                bot.state = DIE;
                break;
            }
        }
    }

    glutPostRedisplay(); // 화면 재 출력
    if (is_missile_throw_timer_on)
        glutTimerFunc(3, MissileThrowTimer, 1);
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
    glutCreateWindow("Battle Cops"); // 윈도우 생성 (윈도우 이름)

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

    if (!shader_manager.Init_Program()) {
        cerr << "Error: Shader Program 생성 실패" << endl;
        std::exit(EXIT_FAILURE);
    }

    shader_program_ID = shader_manager.shader_program_ID;

    bool test = true;
    test &= sphere.Init_VAO(shader_program_ID);
    test &= sky.Init_VAO(shader_program_ID);
    test &= field.Init_VAO(shader_program_ID);
    test &= field2.Init_VAO(shader_program_ID);
    test &= lobby.Init_VAO(shader_program_ID);
    test &= lobby_floor.Init_VAO(shader_program_ID);
    test &= door.Init_VAO(shader_program_ID);
    test &= desk.Init_VAO(shader_program_ID);

    for (size_t i = 0; i < Robot::MAX_BODIES; i++)
    {
        player_robot.bodies[i].is_textured = false;
        test &= player_robot.bodies[i].Init_VAO(shader_program_ID);
    }

    ai_robots.emplace_back(Robot(8.0f, -8.0f));
    ai_robots.emplace_back(Robot(-8.0f, -8.0f));
    ai_robots.emplace_back(Robot(-8.0f, 8.0f));

    for (auto& bot : ai_robots)
        for (size_t i = 0; i < Robot::MAX_BODIES; i++)
        {
            bot.bodies[i].is_textured = false;
            test &= bot.bodies[i].Init_VAO(shader_program_ID);
        }

    if (!test) {
        cerr << "Error: 오브젝트 생성 실패" << endl;
        std::exit(EXIT_FAILURE);
    }

    glutDisplayFunc(drawScene); // 출력 함수의 지정
    glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyPress);
    glutSpecialUpFunc(SpecialKeyUp);
    glutMouseFunc(Mouse);
    glutTimerFunc(100, GameUpdateTimer, 1);
    glutTimerFunc(100, GameStartCheckTimer, 1);
    glutMainLoop(); // 이벤트 처리 시작 
}