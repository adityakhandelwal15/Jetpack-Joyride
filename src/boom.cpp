#include "boom.h"
#include "main.h"

boom::boom(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.004;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.2f,0.5f,0.0f,
        0.0f,0.0f,0.0f,
        0.2f,0.0f,0.0f,

        -0.2f,-0.5f,0.0f,
        0.0f,0.0f,0.0f,
        0.2f,0.0f,0.0f,

        
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void boom::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void boom::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void boom::tick(float xc,float yc ) {
    this->rotation += 5;
    this->position.x += xc;
    this->position.y += yc;

    if (this->position.x> 5 || this->position.x< -5)
    {
        this->position.x = -2;
    }
    
}

