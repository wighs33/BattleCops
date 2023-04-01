#pragma once
#include "Shape.h"

class Cube : public Shape
{
public:
    Cube() { 
        path_ = "Resources/cube.obj";
    }

    void Init_And_Render(int model);

    static const int NUMOF_VERTICES = 6;
};