#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <random>
#include <deque>

using namespace std;

static float WIN_W = 1200.0f, WIN_H = 800.0f;
const int WIN_X = 10, WIN_Y = 10;

const glm::vec3 background_color = glm::vec3(0.0f, 0.0f, 0.0f);

enum Robot_Body {
	LEFT_LEG,
	RIGHT_LEG,
	TORSO,
	LEFT_ARM,
	RIGHT_ARM,
	HEAD,
	NOSE
};

enum Robot_State {
	JUMP_UP,
	JUMP_DOWN,
	IDLE,
	WALK,
	HOLD,
	THROW,
	DIE,
	MOVE_TO_STONE
};

enum Direction {
	DIR_FRONT, 
	DIR_BACK, 
	DIR_LEFT, 
	DIR_RIGHT, 
	DIR_STOP 
};

enum Texture_Image {
	SKY,
	GRASS,
	WALL,
	WOOD,
	WOODFLOOR,
	STONE,
	SOIL
};

static random_device seeder;
static mt19937 eng(seeder());
static uniform_int_distribution<int> dirDist(DIR_FRONT, DIR_RIGHT);
static uniform_real_distribution<double> posDist(-14.8, 14.8);
static uniform_real_distribution<float> missileDir(-180.0f, 180.0f);