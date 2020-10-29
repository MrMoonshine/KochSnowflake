#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "myglfwutil.hpp"
#include "vao_util.hpp"
#include <common/shader.hpp>
using namespace glm;

#define WINDOW_TITLE "My First GLFW Window"
#define TRIANGLE_SIZE 3

int main(void){
    // An array of 3 vectors which represents 3 vertices
    GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };

    std::cout << "Buffer size: " << sizeof(g_vertex_buffer_data) << std::endl;

    Color my_pink(198,33,104);

    MyGlfwUtil mgu("Oida!");
    std::cout << "Hello World! Oida!" << std::endl;
    //glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mgu.create();
    mgu.makeContextCurrent();
    mgu.initGlew();
    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(mgu.window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    //GLuint programID = 1;
    mgu.setBackgroundColor(my_pink);

    VAO vao((GLfloat*)g_vertex_buffer_data,sizeof(g_vertex_buffer_data));
    vao.build();

    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(mgu.window, GLFW_STICKY_KEYS, GL_TRUE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mgu.window)){
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);
        vao.draw();
        /* Swap front and back buffers */
        glfwSwapBuffers(mgu.window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(programID);

    return 0;
}