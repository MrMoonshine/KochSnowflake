#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "myglfwutil.hpp"
#include "vao_util.hpp"
//using namespace VAO;

#define X_OFFSET 0.0f
#define Y_OFFSET 0.0f
#define Z_OFFSET 0.0f
#define PAD_THICC 1.0f

class Triangle{
    private:
        GLfloat height;
        GLfloat side;
        std::vector<GLfloat> a;
        std::vector<GLfloat> b;
        std::vector<GLfloat> c;
    public:
        Triangle(std::vector<GLfloat> a_i,std::vector<GLfloat> b_i,std::vector<GLfloat> c_i);
        Triangle(std::vector<std::vector<GLfloat>> v_i);
        GLfloat getHeight();
        GLfloat getSide();
        std::vector<GLfloat> fullVertex();
};

class Snowflake: public VAO{
    private:
        std::vector<GLfloat> initialTrianglePad();
        GLuint vBuffSize = 0;
        GLfloat vBuff;
        GLuint approxLvl = 0;
        GLuint base_width;
    public:
        Snowflake(GLuint base_width_i = 2);
        using VAO::VAO;
        std::vector<GLfloat> nextApproximation();
};