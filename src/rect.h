#include "main.h"

#ifndef Rect_H
#define Rect_H


class Rect {
public:
    Rect() {}
    Rect(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // Rect_H
