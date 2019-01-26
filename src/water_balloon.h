#include "main.h"

#ifndef water_balloon_H
#define water_balloon_H


class water_balloon {
public:
    water_balloon() {}
    water_balloon(float x, float y, color_t color,int sides);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int p);
    double speed;
private:
    VAO *object;
};

#endif // water_balloon_H
