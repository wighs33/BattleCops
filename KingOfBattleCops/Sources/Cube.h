#pragma once
#include "Shape.h"

class Cube : public Shape
{
public:
    Cube() {
        path_ = "Resources/cube.obj";
    }

    Cube(int face) { 
        path_ = "Resources/cube.obj";
        texturing_face = face;
    }

    virtual void Init_And_Render(int model);

    static const int NUMOF_VERTICES = 36;
};

class Sky : public Cube
{
public:
    Sky() : Cube(CUBE_WHOLE){}

    virtual void Init_And_Render(int model);
};

class Field : public Cube
{
public:
    Field(float scale) : Cube(CUBE_FLOOR) { scale_size = scale; }

    virtual void Init_And_Render(int model);

    float scale_size = 30.0f;

    static const int NUMOF_VERTICES = 6;
};

class Lobby : public Cube
{
public:
    Lobby() : Cube(CUBE_WHOLE) {}

    virtual void Init_And_Render(int model);
};

class Lobby_Floor : public Cube
{
public:
    Lobby_Floor() : Cube(CUBE_FLOOR) {}

    virtual void Init_And_Render(int model);

    static const int NUMOF_VERTICES = 6;
};

class Door : public Cube
{
public:
    Door() : Cube(CUBE_WHOLE) {}

    virtual void Init_And_Render(int model);
};

class Desk : public Cube
{
public:
    Desk() : Cube(CUBE_WHOLE) {}

    virtual void Init_And_Render(int model);
};

class Stone : public Cube
{
public:
    Stone(double x = 0.0f, double z = 0.0f) : pos (glm::vec3(x, 0.0f, z)), Cube(CUBE_WHOLE) {}

    glm::vec3 pos;
    glm::vec3 scale = glm::vec3(0.5f, 0.5f, 0.5f);

    virtual void Init_And_Render(int model);

    int throw_dir = DIR_STOP;
    int throw_time = 0;

    bool is_retained = false;
    glm::vec2 throw_rate;
};