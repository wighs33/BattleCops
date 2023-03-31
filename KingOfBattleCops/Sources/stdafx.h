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

using namespace std;

static float WIN_W = 800.0f, WIN_H = 600.0f;
const int WIN_X = 10, WIN_Y = 10;

const glm::vec3 background_color = glm::vec3(0.0f, 0.0f, 0.0f);

static random_device seeder;
static mt19937 eng(seeder());
static uniform_real_distribution<float> dist(0.0f, 1.0f);