#pragma once
#include "Shape.h"

class Cube : public Shape
{
public:
    Cube() { 
        colors_.resize(36); 
        path_ = "Resources/cube.obj";
    }

    void Init_And_Render(int model);

    static const int NUMOF_VERTICES = 6;

    virtual void Color() {
        fill(colors_.begin(), colors_.end(), glm::vec3(dist(eng), dist(eng), dist(eng)));
    };
};