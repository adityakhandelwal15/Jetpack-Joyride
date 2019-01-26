#include "main.h"

#ifndef dragon_H
#define dragon_H


class dragon {
public:
    dragon() {}
    dragon(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int p);
    double speed;
private:
    VAO *object;
};

#endif // dragon_H
