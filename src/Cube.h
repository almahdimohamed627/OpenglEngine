#ifndef CUBE_H
#define CUBE_H
#include "globals.h"
#include "Entity.h"

class Cube : public Entity {
public:
    Cube();
    void display() override;
};

#endif
