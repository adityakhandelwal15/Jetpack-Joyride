#include "circle.h"
#include "main.h"

circle::circle(float x, float y, color_t color,int sides,float radius) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.004;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    const double PI=3.14159265;
	double r=radius;
	GLfloat vertex_buffer_data[9*sides];
    int j = 0;
	for(int i=0;i<9*sides/2;i+=9){
		double angle=(2*j*PI)/sides;
		vertex_buffer_data[i] = (float)r*cos(angle);
		vertex_buffer_data[i+1] = (float)r*sin(angle);
		vertex_buffer_data[i+2] = 0.0f;

		angle=((j+1)*2*PI)/sides;
		vertex_buffer_data[i+3] = (float)r*cos(angle);
		vertex_buffer_data[i+4] = (float)r*sin(angle);
		vertex_buffer_data[i+5] = 0.0f;

		vertex_buffer_data[i+6] = 0.0f;
		vertex_buffer_data[i+7] = 0.0f;
		vertex_buffer_data[i+8] = 0.0f;
        j++;
	}

    this->object = create3DObject(GL_TRIANGLES, 3*sides/2, vertex_buffer_data, color, GL_FILL);
}

void circle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (180 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void circle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void circle::tick() {
    //this->rotation += speed;
    this->position.x -= 0.01;
    if (this->position.x<-5)
    {
        this->position.x = 4;
    }
    
}

