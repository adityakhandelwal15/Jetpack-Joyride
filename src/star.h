#include "main.h"

#ifndef Star_H
#define Star_H


class Star {
public:
    Star() {}
    Star(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int p);
    double speed;
private:
    VAO *object;
};

#endif // Star_H
