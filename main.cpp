#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "myglfwutil.hpp"
#include "vao_util.hpp"
#include <common/shader.hpp>
#include <time.h>
//#include "SDL.h"
//using namespace glm;

#define WINDOW_TITLE "GLFW Window!"

int main(void){
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

    GLfloat gcbd[] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};

    //::cout << "Buffer size: " << sizeof(g_vertex_buffer_data) << std::endl;
    //std::cout << "Color size: " << sizeof(gcbd) << std::endl;

    Color my_pink(198,33,104);
    //Color my_yellow(1,1,0);
    //Color my_green(0,0.5,0);
    Color my_blue(0,0,0.5);

    std::vector<Color> v_n;
    //Generate A color for each vertex
    srand(time(NULL));
    std::cout << "Hello: " << rand() % 256 << std::endl;
    for(GLuint n = 0; n < 36; n++){;
        v_n.push_back(Color(rand() % 256,rand() % 256,rand() % 256));
    }
    std::cout << "Hello: " << rand() % 256 << std::endl;

    std::cout << "Color Vector Size: " << v_n.size() << std::endl;
    std::cout << "Number of Cube Vertices: " << sizeof(g_vertex_buffer_data)/sizeof(GLfloat)/3 << std::endl;

    MyGlfwUtil mgu(WINDOW_TITLE);
    std::cout << "Hello World! Oida!" << std::endl;
    //mgu.createHints();
    mgu.create();
    mgu.createHints();
    mgu.makeContextCurrent();
    mgu.initGlew();
    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(mgu.window, GLFW_STICKY_KEYS, GL_TRUE);

    //GLuint programID = 1;
    mgu.setBackgroundColor(my_pink);

    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
    GLuint MatrixID = glGetUniformLocation(programID,"MVP");

    //Projection Matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    //Camera MAtrix
    glm::mat4 view = glm::lookAt(
                        glm::vec3(-4,3,3), // Camera is at (4,3,3), in World Space
					    glm::vec3(0,0,0), // and looks at the origin
					    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						); 

    //Model Matrix
    glm::mat4 model = glm::mat4(1.0f);
    
    //ModelViewProjection
    glm::mat4 MVP = projection * view * model;

    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

    VAO vao((GLfloat*)g_vertex_buffer_data,sizeof(g_vertex_buffer_data));
    vao.build();
    //Error in overloaded function with vector<Color>
    vao.setColorbuffer(v_n);
    //vao.setColorbuffer((GLfloat*)gcbd,sizeof(gcbd));
    vao.setColor();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mgu.window)){
        /* Render here */
        mgu.clear();
        glUseProgram(programID);
        glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);
        vao.draw();
        /* Swap front and back buffers */
        glfwSwapBuffers(mgu.window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(programID);
    return 0;
}