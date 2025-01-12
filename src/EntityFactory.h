#include "Entity.h"
#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "List.h"
#include "Sphere.h"

class EntityFactory {
public:
    static Entity *createEntity(const std::string &type, const std::string &name) {
        if(type == "Shape") {
            if(name == "Sphere") {
                return new Sphere();
            }
            else if(name == "Cube") {
                return new Cube();
            }
            else if(name == "Cylinder") {
                return new Cylinder();
            }
        }
        if(type == "List") {
            return new List(name);
        }
        return nullptr;
    }
};
