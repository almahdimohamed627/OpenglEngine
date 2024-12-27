#include "Entity.h"

Entity::Entity()
    : translate_x(Ex), translate_y(E), translate_z(Ez),
      rotate_x(0), rotate_y(0), rotate_z(0),
      scale_x(1), scale_y(1), scale_z(1),
      red(0), green(0), blue(0), alpha(255) {}

void Entity::transform() {
    glColor4ub(red, green, blue, alpha);
    glTranslated(translate_x, translate_y, translate_z);
    glRotated(rotate_x, 1, 0, 0);
    glRotated(rotate_y, 0, 1, 0);
    glRotated(rotate_z, 0, 0, 1);
    glScaled(scale_x, scale_y, scale_z);
}

void Entity::display() {
    glutSolidTeapot(2);
}
