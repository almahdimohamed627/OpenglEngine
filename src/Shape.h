#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include "globals.h"
#include "Entity.h"
#include "json.hpp"
#include <GL/freeglut.h>
using json = nlohmann::json;
// Base Shape class
class Shape : public Entity {
protected:
    double red, green, blue, alpha;

public:
    Shape();
    Shape(double x, double y, double z);
    Shape(Entity *p_perant, double x, double y, double z);
    Shape(Shape* e);
    void setColor(int red, int green, int blue, int alpha);
    void applyTransformation() override;
    void display() override;
    void displayInfo() override;
    json toJSON() override;
    void fromJSON(const json &j) override;
    void fromJSON(const json &j, int p_id);
    Shape* clone() override;
};

#endif
