#include "main.h"

#ifndef ice_H
#define ice_H


class ice {
public:
    ice() {}
    ice(float x, float y, color_t color,int sides);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // ice_H
