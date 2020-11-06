#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "myglfwutil.hpp"
#include "vao_util.hpp"
//using namespace VAO;

#define X_ORIGIN 0.0f
#define Y_ORIGIN 2.0f
#define Z_ORIGIN 3.0f
#define PAD_THICC 1.0f
//Vector placement to convert from
//Carthesian to spherical coordinates
#define T_AMOUNT 0
#define T_THETA 1
#define T_PHI 

#define TERMINATE_BRANCH GL_TRUE

class Triangle{
    private:
        GLfloat height;
        GLfloat side;
        std::vector<GLfloat> a;
        std::vector<GLfloat> b;
        std::vector<GLfloat> c;
    public:
        Triangle();
        Triangle(std::vector<GLfloat> a_i,std::vector<GLfloat> b_i,std::vector<GLfloat> c_i);
        Triangle(std::vector<std::vector<GLfloat>> v_i);
        void build(std::vector<GLfloat> a_i,std::vector<GLfloat> b_i,std::vector<GLfloat> c_i);
        void build(std::vector<GLfloat> v_i);
        std::vector<GLfloat> getA();
        std::vector<GLfloat> getB();
        std::vector<GLfloat> getC();
        GLfloat getHeight();
        GLfloat getSide();
        std::vector<GLfloat> fullVertex();
};

namespace vec3_2d{
   using std::vector; 
   const GLuint left = GL_TRUE;
   const GLuint right = GL_FALSE;

   class Vec2p5{
       private:
            vector<GLfloat> myVec;
            GLfloat r;
            GLfloat phi;
       public:
            Vec2p5(vector<GLfloat> v_i);
            Vec2p5 operator+(const Vec2p5 &a);
            Vec2p5 operator-(const Vec2p5 &a);
            Vec2p5 operator/(const GLfloat &a);
            Vec2p5 operator*(const GLfloat &a);
            GLboolean operator<(const GLfloat &a);
            GLboolean operator>(const GLfloat &a);
            GLboolean operator==(const GLfloat &a);
            GLboolean operator<=(const GLfloat &a);
            GLboolean operator>=(const GLfloat &a);
            Vec2p5 normalV2p5(Vec2p5 a);
            vector<GLfloat> getVector();
            GLfloat getLength();
            GLfloat getAngle();
   };

    void dump(vector<GLfloat> v_i); 
    vector<GLfloat> normalVector(vector<GLfloat> v_i, GLuint direction_i = left);

    //This function will get a starting point and a vector.
    //The new Triangle will be appended on the left side of the vector 
    Triangle getNext(vector<GLfloat> point_i, Vec2p5 vector_i, GLuint direction_i = left);
    vector<Triangle> build_branch(vector<GLfloat> point_i, Vec2p5 vector_i,GLuint iteration_i);

    GLuint vertices_amount(GLuint iteration_i);
    vector<GLfloat> triangles2floatvec(vector<Triangle> a);
}

class Snowflake: public VAO{
    private:
        std::vector<GLfloat> initialTrianglePad(GLuint s_i);
        GLfloat base_width;
        Triangle *base;
    public:
        Snowflake(GLuint base_width_i = 2,GLuint depth_i = 2);
        using VAO::VAO;
        std::vector<GLfloat> nextApproximation();
};