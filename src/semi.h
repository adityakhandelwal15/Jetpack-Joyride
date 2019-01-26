#include "main.h"

#ifndef semi_H
#define semi_H


class semi {
public:
    semi() {}
    semi(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int p);
    double speed;
private:
    VAO *object;
};

#endif // semi_H
