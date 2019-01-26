#include "main.h"

#ifndef circle_H
#define circle_H


class circle {
public:
    circle() {}
    circle(float x, float y, color_t color,int sides,float radius);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // circle_H
