#include "main.h"

#ifndef tri_H
#define tri_H


class tri {
public:
    tri() {}
    tri(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // tri_H
