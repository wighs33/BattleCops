#pragma once
#include "Shape.h"

class Cube : public Shape
{
public:
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
    Sky() : Cube(FRONT){}

    virtual void Init_And_Render(int model);

    static const int NUMOF_VERTICES = 6;
};

class Field : public Cube
{
public:
    Field() : Cube(FLOOR) {}

    virtual void Init_And_Render(int model);

    static const int NUMOF_VERTICES = 6;
};

class Lobby : public Cube
{
public:
    Lobby() : Cube(WHOLE) {}

    virtual void Init_And_Render(int model);
};

class Lobby_Floor : public Cube
{
public:
    Lobby_Floor() : Cube(FLOOR) {}

    virtual void Init_And_Render(int model);

    static const int NUMOF_VERTICES = 6;
};

class Door : public Cube
{
public:
    Door() : Cube(WHOLE) {}

    virtual void Init_And_Render(int model);
};