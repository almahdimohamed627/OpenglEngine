#include "Entity.h"

int Entity::count = 0;      // Definition of static variable
int Entity::selectedIndex = 0;  

Entity::Entity()
    : translate_x(Ex), translate_y(E), translate_z(Ez),
      rotate_x(0), rotate_y(0), rotate_z(0),
      scale_x(1), scale_y(1), scale_z(1),
      red(0), green(0), blue(0), alpha(255) {
        selectedIndex = count;
        id = count;
        count +=1;
      }

void Entity::transform() {
    glColor4ub(red, green, blue, alpha);
    if(selectedIndex ==id) {
        glColor4ub(255, 0, 0, 255);
    }
    glTranslated(translate_x, translate_y, translate_z);
    glRotated(rotate_x, 1, 0, 0);
    glRotated(rotate_y, 0, 1, 0);
    glRotated(rotate_z, 0, 0, 1);
    glScaled(scale_x, scale_y, scale_z);
}

void Entity::display() {
    glPushMatrix();
    transform();
    glutSolidTeapot(2);
    glPopMatrix();
}

    int Entity::selected() {
        return selectedIndex;
    }
    int Entity::selected(int index) {
        selectedIndex += index;
        if(selectedIndex >= count) {
            selectedIndex =0;
        }
        else if(selectedIndex < 0) {
            selectedIndex =count-1;
        }
        return selectedIndex;
    }
