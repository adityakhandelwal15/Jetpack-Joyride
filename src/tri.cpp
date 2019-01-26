#include "tri.h"
#include "main.h"

tri::tri(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.004;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a tri.
    // A cube has 6 faces with 2 tris each, so this makes 6*2=12 tris, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.150f,0.0f,0.0f,
        0.150f,0.0f,0.0f,
        0.0f,-0.30f,0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void tri::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void tri::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void tri::tick() {
    //this->rotation += speed;
    //this->position.x -= p*speed;
    
}

