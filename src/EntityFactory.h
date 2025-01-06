#include "Entity.h"
#include "Shape.h"
#include "Cube.h"
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
        }
        if(type == "List") {
            return new List(name);
        }
        return nullptr;
    }
};
