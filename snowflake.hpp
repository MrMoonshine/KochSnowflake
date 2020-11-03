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

#define X_ORIGIN 0.0f
#define Y_ORIGIN 0.0f
#define Z_ORIGIN 0.0f
#define PAD_THICC 1.0f
//Vector placement to convert from
//Carthesian to spherical coordinates
#define T_AMOUNT 0
#define T_THETA 1
#define T_PHI 2

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
        std::vector<GLfloat> getA();
        std::vector<GLfloat> getB();
        std::vector<GLfloat> getC();
        std::vector<GLfloat> getCenter();
        GLfloat getHeight();
        GLfloat getSide();
        std::vector<GLfloat> fullVertex();
};

struct SnowSpike{
    Triangle base;
    GLfloat base_angle;
    SnowSpike* childA;
    SnowSpike* childB;
};

class Snowflake: public VAO{
    private:
        std::vector<GLfloat> initialTrianglePad(GLuint s_i);
        //This function returns the inner radius of a triangle
        //all sides must be the same
        GLfloat centerdistance(GLfloat side_i);
        //This function returns the height of a triangle
        GLfloat height(GLfloat side_i);
        //returns the distance from the center to the new children corner
        GLfloat childCornerDist(GLfloat side_i);
        //This function returns the center of the next 
        //middle_i is the center of the parent
        //dist_i is distance to be added e.g height to center * 1.5 for new center
        //angle_i is the angle whrere the next triangle should be created
        std::vector<GLfloat> nextHop(std::vector<GLfloat> middle_i ,GLfloat dist_i, GLfloat angle_i);
        //Calls the function above and calculates the triangle
        //side_i is the length of the parent's side
        Triangle createChild(std::vector<GLfloat> middle_i ,GLfloat side_i, GLfloat angle_i);
        std::vector<GLfloat> center;
        GLuint vBuffSize = 0;
        GLfloat vBuff;
        GLuint approxLvl = 0;
        GLuint depth = 0;
        GLfloat base_width;
        Triangle base;
        std::vector<SnowSpike> spikes;
    public:
        Snowflake(GLuint base_width_i = 2,GLuint depth_i = 2);
        using VAO::VAO;
        std::vector<GLfloat> nextApproximation();
};