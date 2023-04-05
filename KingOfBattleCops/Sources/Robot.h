#pragma once
#include "Cube.h"

class Robot
{
public:
	Robot(double x, double z) : pos(glm::vec3(x, 0.0, z)) {}

	void Init_And_Render(int model);

	void Init_And_Render_Left_Leg(int model);
	void Init_And_Render_Right_Leg(int model);
	void Init_And_Render_Torso(int model);
	void Init_And_Render_Left_Arm(int model);
	void Init_And_Render_Right_Arm(int model);
	void Init_And_Render_Head(int model);
	void Init_And_Render_Nose(int model);

	static const int MAX_BODIES = 7;

	Cube bodies[MAX_BODIES];

	float x_rotate = 0.0f;
	float y_rotate = 0.0f;
	float z_rotate = 0.0f;

	glm::vec3 pos;

	const float rotate_rate = 5.0f;
	const float move_rate = 0.1f;

	bool is_forward = false;

	glm::vec3 leg_and_arm_size = glm::vec3(0.1, 0.4, 0.1);

	int jump;
	int dir = DIR_BACK;
	int state = IDLE;

	int retained_stone_index = -1;
};

