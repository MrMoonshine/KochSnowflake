#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include "snowflake.hpp"

Snowflake::Snowflake(GLuint base_width_i) : VAO(initialTrianglePad()){
    base_width = base_width_i;
    //std::cout << "Snowflake buffer: " << buffer_size << std::endl;
}

std::vector<GLfloat> Snowflake::initialTrianglePad(){
    std::vector<GLfloat> p1 = {-1.0f,1.0f,2.0f};
    std::vector<GLfloat> p2 = {1.0f,1.0f,2.0f};
    std::vector<GLfloat> p3 = {0.0f,-1.0f,2.0f};
    Triangle t1(p1,p2,p3);
    std::vector<GLfloat> v_s = t1.fullVertex();
    return v_s;
}

std::vector<GLfloat> Snowflake::nextApproximation(){
    std::cout << "Further Approximations" << std::endl;
}

Triangle::Triangle(std::vector<GLfloat> a_i,std::vector<GLfloat> b_i,std::vector<GLfloat> c_i){
    a = a_i;
    b = b_i;
    c = c_i;
}

Triangle::Triangle(std::vector<std::vector<GLfloat>> v_i) : Triangle(v_i[0],v_i[1],v_i[2]){}

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

GLfloat Triangle::getHeight(){
    return height;
}

GLfloat Triangle::getSide(){
    return side;
}