#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
    Sphere() {
        path_ = "Resources/sphere.obj";
    }

    void Init_And_Render(int model);

    static const int NUMOF_VERTICES = 2880;
};