#include "main.h"

#ifndef ignition_H
#define ignition_H


class ignition {
public:
    ignition() {}
    ignition(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // ignition_H
