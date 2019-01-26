#include "main.h"

#ifndef boom_H
#define boom_H


class boom {
public:
    boom() {}
    boom(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float xc,float yc);
    double speed;
private:
    VAO *object;
};

#endif // boom_H
