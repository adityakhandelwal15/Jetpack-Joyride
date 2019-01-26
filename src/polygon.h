#include "main.h"

#ifndef polygon_H
#define polygon_H


class polygon {
public:
    polygon() {}
    polygon(float x, float y, color_t color,int sides);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // polygon_H
