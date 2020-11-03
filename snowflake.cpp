#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include "snowflake.hpp"

Snowflake::Snowflake(GLuint base_width_i,GLuint depth_i) : VAO(initialTrianglePad(base_width_i)){
    depth = depth_i;
    center = {base_width / 2.0f + X_ORIGIN,centerdistance(base_width) + Y_ORIGIN,Z_ORIGIN};
    SnowSpike s1;
    s1.base_angle = (M_PI/6.0f);
    
    std::vector<GLfloat> nc = nextHop(center,childCornerDist(base_width),s1.base_angle);
    //std::cout << "Height to Center: " << centerdistance(base_width) << std::endl;
    for(auto a : nc){
        std::cout << "NC Vector: " << a << std::endl;
    }
    s1.base = createChild(center,base_width,s1.base_angle);
    for(auto a : s1.base.fullVertex()){
        std::cout << "NC Triangle: " << a << std::endl;
    }
}

std::vector<GLfloat> Snowflake::initialTrianglePad(GLuint s_i){
    base_width = (GLfloat)s_i;
    GLfloat height_s = sqrt(pow(base_width,2) - pow(base_width/2,2));
    //std::cout << "My Height is" << height_s << std::endl;
    std::vector<GLfloat> p1 = {X_ORIGIN,Y_ORIGIN,Z_ORIGIN};
    std::vector<GLfloat> p2 = {base_width + X_ORIGIN,Y_ORIGIN,Z_ORIGIN};
    std::vector<GLfloat> p3 = {base_width / 2.0f + X_ORIGIN,height_s + Y_ORIGIN,Z_ORIGIN};
    Triangle t1(p1,p2,p3);
    base = t1;
    std::vector<GLfloat> v_s = t1.fullVertex();
    return v_s;
}

GLfloat Snowflake::centerdistance(GLfloat side_i){
    return side_i*tan(M_PI/6.0f)/2;
}

GLfloat Snowflake::height(GLfloat side_i){
    return sqrt(pow(side_i,2) - pow(side_i/2.0f,2));
}

GLfloat Snowflake::childCornerDist(GLfloat side_i){
    return centerdistance(side_i) + height(side_i/3);
}

Triangle Snowflake::createChild(std::vector<GLfloat> middle_i ,GLfloat side_i, GLfloat angle_i){
    //This is the point of the new corner
    std::vector<GLfloat> p1 = nextHop(middle_i,childCornerDist(side_i),angle_i);
    //PI/6 (30°) in each direction
    GLfloat phi_a = angle_i - 5 * M_PI/6.0f;
    GLfloat phi_b = angle_i + 5 * M_PI/6.0f;
    std::vector<GLfloat> p2 = nextHop(p1,side_i/3.0f,phi_a);
    std::vector<GLfloat> p3 = nextHop(p1,side_i/3.0f,phi_b);
    return Triangle(p1,p2,p3);
}

std::vector<GLfloat> Snowflake::nextHop(std::vector<GLfloat> middle_i ,GLfloat dist_i, GLfloat angle_i){
    std::vector<GLfloat> p_n = middle_i;
    p_n[0] += dist_i * cos(angle_i);
    p_n[1] += dist_i * sin(angle_i);
    return p_n;
}

std::vector<GLfloat> Snowflake::nextApproximation(){
    std::cout << "Further Approximations" << std::endl;
}

Triangle::Triangle(){}

Triangle::Triangle(std::vector<GLfloat> a_i,std::vector<GLfloat> b_i,std::vector<GLfloat> c_i){
    build(a_i,b_i,c_i);
}

Triangle::Triangle(std::vector<std::vector<GLfloat>> v_i) : Triangle(v_i[0],v_i[1],v_i[2]){}

void Triangle::build(std::vector<GLfloat> a_i,std::vector<GLfloat> b_i,std::vector<GLfloat> c_i){
    a = a_i;
    b = b_i;
    c = c_i;
}

std::vector<GLfloat> Triangle::fullVertex(){
    std::vector<GLfloat> v_o;

    for(auto i : a)
    v_o.push_back(i);

    for(auto i : b)
    v_o.push_back(i);

    for(auto i : c)
    v_o.push_back(i);

    return v_o;
}

std::vector<GLfloat> Triangle::getCenter(){
    //Will be used later. maybe?
    return a;
}

GLfloat Triangle::getHeight(){
    return height;
}

GLfloat Triangle::getSide(){
    return side;
}

std::vector<GLfloat> Triangle::getA(){return a;}
std::vector<GLfloat> Triangle::getB(){return b;}
std::vector<GLfloat> Triangle::getC(){return c;}