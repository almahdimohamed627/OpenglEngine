#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include "globals.h"
#include "json.hpp"
#include <GL/freeglut.h>

using json = nlohmann::json;
// Base Entity class
class Entity {
protected:
    double translate_x, translate_y, translate_z;
    double rotate_x, rotate_y, rotate_z;
    double scale_x, scale_y, scale_z;
    std::string type; 
    std::string name;
    Entity *p_perant;
    int id, p_id;
    static int selectedIndex;
    static int count;

public:
    Entity();
    Entity(double x, double y, double z);
    Entity(Entity *p_perant, double x, double y, double z);
    Entity(Entity* e);
    virtual ~Entity();
    static int selected();
    static void selected(int index);
    int getId();
    Entity* getPerant();
    std::string getName();
    std::string getType();
    double getX(); double getY(); double getZ();
    virtual void applyTransformation();
    void transform(char transformation, bool x, bool y, bool z, int amount);
    void translate(double x, double y, double z);
    virtual void display();
    virtual void displayInfo();
    virtual json toJSON();
    virtual void fromJSON(const json &j);
    virtual void fromJSON(const json &j, int p_id);
    virtual Entity* clone() = 0; // Pure virtual method

};

#endif
