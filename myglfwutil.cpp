#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "myglfwutil.hpp"
#include "vao_util.hpp"

VAO::VAO(GLfloat *buffer_data_i, GLuint length_i){
    buffer_size = length_i;
    buffer_data = buffer_data_i;
}

VAO::~VAO(){
    // Cleanup VBO
	glDeleteBuffers(1, &buffer);
    glDeleteBuffers(1,&colorbuffer);
	glDeleteVertexArrays(1, &arrayID);

    std::cout << "Cleaned up VAO" << std::endl;
}

void VAO::build(){
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, buffer_data, GL_STATIC_DRAW);
}

void VAO::draw(){
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
}

void VAO::setColorbuffer(std::vector<Color> buff_i){
    color_vector = buff_i;
}

std::vector<GLfloat> VAO::color_vector_float(){
    std::vector<GLfloat> outvec;
    for(Color x : color_vector){
        outvec.push_back(x.red);
        outvec.push_back(x.green);
        outvec.push_back(x.blue);
    }
    return outvec;
}

void VAO::setColor(){
    std::vector<GLfloat> vec1 = color_vector_float();
    GLfloat colorArr[vec1.size()];
    std::copy(vec1.begin(),vec1.end(),colorArr);

    glGenBuffers(1,&colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,colorbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colorArr),colorArr,GL_STATIC_DRAW);

    //std::cout << "Buffersize: " << color_buffer_size << " ID: " << colorbuffer << std::endl;
}

void MyGlfwUtil::clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

MyGlfwUtil::MyGlfwUtil(std::string title_i){
    window_title = title_i;

    if (!glfwInit())
        throw "Failed to load GLFW";
}

MyGlfwUtil::~MyGlfwUtil(){
    std::cout << "Closing Window. Goodbye" << std::endl;
    glfwTerminate();
}

void MyGlfwUtil::create(GLuint width, GLuint height){
    window = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);
    if (!window){
        glfwTerminate();
        throw "Failed to create a Window!";
        return;
    }

    glClearColor(0,0,0,0);
}

void MyGlfwUtil::makeContextCurrent(){
    glfwMakeContextCurrent(window);
}

GLenum MyGlfwUtil::initGlew(){
    // Initialize GLEW
	glewExperimental = true; // Needed for core profile
    GLenum glew_staus = glewInit();
	if (glew_staus != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
		getchar();
		glfwTerminate();
        throw "Unable to initialize GLEW";
	}
    return glew_staus;
}

void MyGlfwUtil::setBackgroundColor(GLfloat r,GLfloat g, GLfloat b, GLfloat alpha){
    glClearColor(r,g,b, alpha);
}

void MyGlfwUtil::setBackgroundColor(Color color){
    glClearColor(color.red,color.green,color.blue,color.alpha);
}

void MyGlfwUtil::createHints(){
    //Doesn't work somehow?
    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Color::Color(GLfloat r,GLfloat g, GLfloat b, GLfloat a){
    if(r > 1 || g > 1 || b > 1 || a > 1){
        red = r/255.0;
        green = g/255.0;
        blue = b/255.0;
        alpha = a/255.0; 
    }else{
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
    
}

Color::~Color(){

}

