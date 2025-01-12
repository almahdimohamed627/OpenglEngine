#ifndef LIST_H
#define LIST_H
#include "globals.h"
#include <string>
#include "Entity.h"
#include <GL/freeglut.h>
#include "MyVector.h"

class List : public Entity {
protected:

public:
    MyVector m_entities;
    List(std::string name);
    List(std::string name, double x, double y, double z);
    List(Entity *p_perant, std::string name);
    List(List* e);
    void display() override;
    void displayInfo() override;
    void pushEntity(Entity *e);
    bool empty();
    json toJSON() override;
    void fromJSON(const json &j) override;
    void fromJSON(const json &j, int p_id) override;
    std::string getDisplayCode() override;
    std::string getDisplayCode(int id);
    std::string getListCode(int id);
    List* clone() override;
};

#endif
