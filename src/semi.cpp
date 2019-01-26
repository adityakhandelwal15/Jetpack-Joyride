#include "semi.h"
#include "main.h"

semi::semi(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.004;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0.5f,0.866025f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.1f,0.0f,

        0.5f,0.866025f,0.0f,
        0.5f,0.966021f,0.0f,
        0.0f,1.1f,0.0f,

//ss
        0.866025f,0.5f,0.0f,
        0.5f,0.866025f,0.0f,
        0.5f,0.966021f,0.0f,

        0.866025f,0.5f,0.0f,
        0.9660251f,0.5f,0.0f,
        0.5f,0.966021f,0.0f,



//dd
        // 0.866025f,0.5f,0.0f,
        // 1.0f,0.0f,0.0f,
        // 1.1f,0.0f,0.0f,

        // 0.866025f,0.5f,0.0f,
        // 0.876025f,0.61,0.0f,
        // 1.1f,0.0f,0.0f,
        1.1f,0.0f,0.0f,
        0.866025f,0.5f,0.0f,
        0.9660251f,0.5f,0.0f,

        1.0f,0.0f,0.0f,
        1.1f,0.0f,0.0f,
        0.866025f,0.5f,0.0f,

//bdhd

        1.1f,0.0f,0.0f,
        0.866025f,-0.5f,0.0f,
        0.9660251f,-0.5f,0.0f,

        1.0f,0.0f,0.0f,
        1.1f,0.0f,0.0f,
        0.866025f,-0.5f,0.0f,



//bhbfh
        0.866025f,-0.5f,0.0f,
        0.5f,-0.866025f,0.0f,
        0.5f,-0.966021f,0.0f,

        0.866025f,-0.5f,0.0f,
        0.9660251f,-0.5f,0.0f,
        0.5f,-0.966021f,0.0f,


//ncjnc
        0.5f,-0.866025f,0.0f,
        0.0f,-1.0f,0.0f,
        0.0f,-1.1f,0.0f,

        0.5f,-0.866025f,0.0f,
        0.5f,-0.966021f,0.0f,
        0.0f,-1.1f,0.0f,

        
    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void semi::draw(glm::mat4 VP) {
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

void semi::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void semi::tick(int p) {
    this->position.x -= 0.01;
    if (this->position.x < -5)
    {
        this->position.x = 5;
    }
    this->position.y += p*0.02;
    
}

