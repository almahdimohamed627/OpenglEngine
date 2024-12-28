#ifndef CUBE_H
#define CUBE_H
#include "globals.h"
#include "Entity.h"

class Cube : public Entity {
public:
    void display() override;
};

#endif
