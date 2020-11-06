#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "myglfwutil.hpp"
//#include "vao_util.hpp"
#include <MmGL/shader.hpp>
#include <MmGL/input.hpp>
#include "snowflake.hpp"
#include <time.h>
//#include "SDL.h"
//using namespace glm;

#define WINDOW_TITLE "GLFW Window!"
#define MY_VERTEX_SHADER "TransformVertexShader.glsl"
#define MY_FRAGMENT_SHADER "ColorFragmentShader.glsl"
#define COLORFUL GL_FALSE
#define SNOWFLAKE_ITERATIONS 10
#define SNOWFLAKE_SIZE 12

int main(void){
	//std::cout << "Snowflake Main Test: " << oida.test << std::endl;
    // An array of 3 vectors which represents 3 vertices
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

    Color my_pink(198,33,104);
	Color my_grey(38,38,38);

    std::vector<Color> v_n;
    //Generate A color for each vertex
    

    for(GLuint n = 0; n < 36; n++){;
        v_n.push_back(Color(rand() % 256,rand() % 256,rand() % 256));
    }

    //std::cout << "Color Vector Size: " << v_n.size() << std::endl;
    //std::cout << "Number of Cube Vertices: " << sizeof(g_vertex_buffer_data)/sizeof(GLfloat)/3 << std::endl;
	std::cout << "Created random cube Colors" << std::endl;
    MyGlfwUtil mgu(WINDOW_TITLE);
    //mgu.createHints();
    mgu.create();
    mgu.makeContextCurrent();
    mgu.initGlew();
    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(mgu.window, GLFW_STICKY_KEYS, GL_TRUE);

    mgu.setBackgroundColor(my_grey);

	std::cout << "Created GLFW-Window" << std::endl;

	Input uinp(mgu.window);
	std::cout << "Loaded User Input" << std::endl;

	Shader shader1(MY_VERTEX_SHADER,MY_FRAGMENT_SHADER);
	std::cout << "Created shaders" << std::endl;

	GLuint MatrixID = glGetUniformLocation(shader1.id,"MVP");


    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

    VAO vao((GLfloat*)g_vertex_buffer_data,sizeof(g_vertex_buffer_data));
    vao.build();
    vao.setColorbuffer(v_n);
    vao.setColor();

	Snowflake koch(SNOWFLAKE_SIZE,SNOWFLAKE_ITERATIONS);
	std::cout << "Oida Oida" << std::endl;
	koch.build();
	if(COLORFUL)
	koch.randomizeVertexColors();
	else
	koch.singleColor(my_pink);

	//koch.showBuffers();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mgu.window)){
        /* Render here */
        mgu.clear();

		shader1.setFloat("someUniform",1.0f);
        shader1.use();
		
		uinp.computeMatrices();

		glm::mat4 projection = uinp.getProjectionMatrix();
		glm::mat4 view = uinp.getViewMatrix();
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 MVP = projection * view * modelMatrix;

        glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);
		vao.draw();
		koch.draw();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(mgu.window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    return 0;
}