
#include "ice.h"
#include "main.h"

ice::ice(float x, float y, color_t color,int sides) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.004;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    const double PI=3.14159265;
	double r=0.2;
	GLfloat vertex_buffer_data[9*sides];
	for(int i=0;i<9*sides;i+=9){

		double angle=i*2*PI/sides;
		vertex_buffer_data[i] = (float)r*cos(angle);
		vertex_buffer_data[i+1] = (float)r*sin(angle);
		vertex_buffer_data[i+2] = 0.0f;

		angle=(i+1)*2*PI/sides;
		vertex_buffer_data[i+3] = (float)r*cos(angle);
		vertex_buffer_data[i+4] = (float)r*sin(angle);
		vertex_buffer_data[i+5] = 0.0f;

		vertex_buffer_data[i+6] = 0.0f;
		vertex_buffer_data[i+7] = 0.0f;
		vertex_buffer_data[i+8] = 0.0f;
	}

    this->object = create3DObject(GL_TRIANGLES, 3*sides, vertex_buffer_data, color, GL_FILL);
}

void ice::draw(glm::mat4 VP) {
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

void ice::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void ice::tick() {
   // this->rotation += speed;
    this->position.x -= 0.04;
    this->position.y -= 0.01;

    
}

