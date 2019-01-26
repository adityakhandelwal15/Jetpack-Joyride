#include "main.h"

#ifndef line_H
#define line_H


class line {
public:
    line() {}
    line(float x, float y, color_t color,int angle);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // line_H
