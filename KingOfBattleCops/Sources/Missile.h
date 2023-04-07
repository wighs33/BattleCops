#pragma once
#include "Shape.h"

class Missile : public Shape
{
public:
	Missile(double x, double z) : pos(glm::vec3(x, -0.5f, z)){
		path_ = "Resources/missile.obj";
	}

    virtual void Init_And_Render(int model);

	glm::vec3 pos = glm::vec3(0.0f, -0.5f, 0.0f);

    static const int NUMOF_VERTICES = 1704;

	float y_rotate = 0.0f;

	int throw_dir = DIR_STOP;
	int throw_time = 0;
};

