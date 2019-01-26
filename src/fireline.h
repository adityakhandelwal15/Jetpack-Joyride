#include "main.h"

#ifndef fireline_H
#define fireline_H


class fireline {
public:
    fireline() {}
    fireline(float x, float y, color_t color,int sides,float radius);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // fireline_H
