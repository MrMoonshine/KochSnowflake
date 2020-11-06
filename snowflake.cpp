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
    base_width = base_width_i;

    using vec3_2d::Vec2p5;
    using std::vector;

    vector<Vec2p5> mainEdges;
    vector<Vec2p5> mainCorners;

    Vec2p5 vba(base->getA());
    Vec2p5 vbb(base->getC());
    Vec2p5 vbc(base->getB());
    mainEdges.push_back(vbb - vba);
    mainEdges.push_back(vbc - vbb);
    mainEdges.push_back(vba - vbc);
    
    mainCorners.push_back(vba);
    mainCorners.push_back(vbb);
    mainCorners.push_back(vbc);
    vector<Triangle> finalTV;
    for(GLuint a = 0; a<mainEdges.size();a++){
        vector<Triangle> tv = vec3_2d::build_branch(mainCorners[a].getVector(),mainEdges[a],depth_i);
        finalTV.insert(finalTV.end(),tv.begin(),tv.end());
    }
    vector<GLfloat> myBranch = vec3_2d::triangles2floatvec(finalTV);
    buffer_vector.insert(buffer_vector.end(),myBranch.begin(),myBranch.end());
    std::cout << "myBranch size = " << myBranch.size() << std::endl;
    vec3_2d::dump(buffer_vector);
    std::cout << "buffer_vector size = " << buffer_vector.size() << " therefore: " << buffer_vector.size()/9 << " Vertices" << std::endl;
    //for(GLuint n = 0 ; n < 12 ; n++)
    //std::cout << "Number of vertices for " << n << " Iterations: " << vec3_2d::vertices_amount(n) << std::endl;
}

std::vector<GLfloat> Snowflake::initialTrianglePad(GLuint s_i){
    base_width = (GLfloat)s_i;
    GLfloat height_s = sqrt(pow(base_width,2) - pow(base_width/2,2));
    //std::cout << "My Height is" << height_s << std::endl;
    std::vector<GLfloat> p1 = {X_ORIGIN,Y_ORIGIN,Z_ORIGIN};
    std::vector<GLfloat> p2 = {base_width + X_ORIGIN,Y_ORIGIN,Z_ORIGIN};
    std::vector<GLfloat> p3 = {base_width / 2.0f + X_ORIGIN,height_s + Y_ORIGIN,Z_ORIGIN};
    //Yes... this pointer is neccesary :(
    base = new Triangle(p1,p2,p3);
    std::vector<GLfloat> v_s = base->fullVertex();
    return v_s;
}

std::vector<GLfloat> Snowflake::nextApproximation(){
    std::cout << "Further Approximations" << std::endl;
}

void vec3_2d::dump(vector<GLfloat> v_i){
    using std::cout;
    if(v_i.size() % 3 == 0){
        if(v_i.size() == 9)
        cout << "--Printing Vertices--" << std::endl;
        else if(v_i.size() == 3)
        cout << "---Printing Vector---" << std::endl;
        else
        cout << "--Printing " << v_i.size()/9 << " Vertices--" << std::endl;

        for(GLuint a=0;a<v_i.size()/3;a++){
            cout << v_i[3*a] << "\t" << v_i[3*a + 1] << "\t" << v_i[3*a + 2] << "\t" << std::endl; 
        }
        cout << "---------------------" << std::endl;
    }
    else{
        for(auto a : v_i)
        cout << a << std::endl;
    }
    
}

Triangle vec3_2d::getNext(vector<GLfloat> point_i, Vec2p5 vector_i, GLuint direction_i){
    //Points for the triangle
    vector<GLfloat> p1_o;
    vector<GLfloat> p2_o;
    vector<GLfloat> p3_o;

    Vec2p5 point_s(point_i);
    GLfloat parentSide =vector_i.getLength();

    Vec2p5 height_s(normalVector(vector_i.getVector(),direction_i));
    //The height of the child triangle
    //divide by 3 because it's the length of the child
    GLfloat childHeight = (parentSide/3.0f) * sin(M_PI/3.0f);
    //Shorten the height-vector by the ratio of the actual height and itself
    height_s = height_s * (childHeight / height_s.getLength());
    //Add half inputVector to the pint
    //Add height vector => Point
    p1_o = (point_s + ((vector_i/2) + height_s)).getVector();
    p2_o = (point_s + (vector_i*(2.0f/3.0f))).getVector();
    p3_o = (point_s + (vector_i*(1.0f/3.0f))).getVector();

    return Triangle(p1_o,p2_o,p3_o);
}

std::vector<Triangle> vec3_2d::build_branch(vector<GLfloat> point_i, Vec2p5 vector_i,GLuint iteration_i){
    Vec2p5 point_s(point_i); //just for convenience
    GLuint verticesAmount = vertices_amount(iteration_i);
    //The first triangle will be the base from which every calculation starts
    vector<Triangle> openSet = {getNext(point_i,vector_i)};
    vector<Triangle> closedSet;

    //Create infinite Triangles until you reach your limit of Vertices
    while(openSet.size() && closedSet.size() < verticesAmount){
        Vec2p5 start_L(openSet[0].getC());
        Vec2p5 start_R(openSet[0].getA());
        Vec2p5 redundantCorner(openSet[0].getB());
        openSet.push_back(getNext(start_L.getVector(),(start_R - start_L)));
        openSet.push_back(getNext(start_R.getVector(),(redundantCorner - start_R)));
        closedSet.push_back(openSet[0]);
        openSet.erase(openSet.begin());
    }

    return closedSet;
}

std::vector<GLfloat> vec3_2d::triangles2floatvec(vector<Triangle> a){
    vector<GLfloat> v_o;
    for(auto b : a){
        vector<GLfloat> t1 = b.fullVertex();
        v_o.insert(v_o.end(),t1.begin(),t1.end());
    }
    return v_o;
}

std::vector<GLfloat> vec3_2d::normalVector(vector<GLfloat> v_i, GLuint direction_i){
    //True = left, False = right
    if(direction_i)
    return {-v_i[1],v_i[0],v_i[2]};
    else
    return {v_i[1],-v_i[0],v_i[2]};
}

GLuint vec3_2d::vertices_amount(GLuint iteration_i){
    GLuint numberOfVertices = 0;
    for(GLuint i=0;i<iteration_i;i++)
    numberOfVertices += 1 << i;

    return numberOfVertices;
}

vec3_2d::Vec2p5::Vec2p5(vector<GLfloat> v_i){
    myVec = v_i;
    r = sqrt(pow(myVec[0],2) + pow(myVec[1],2));
    phi = asin(myVec[1]/r);
}

GLfloat vec3_2d::Vec2p5::getLength(){
    return r;
}

GLfloat vec3_2d::Vec2p5::getAngle(){
    return phi;
}

vec3_2d::Vec2p5 vec3_2d::Vec2p5::operator/(const GLfloat &a){
    return Vec2p5({(this->myVec[0] / a),(this->myVec[1] / a),(this->myVec[2] / a)});
}

vec3_2d::Vec2p5 vec3_2d::Vec2p5::operator*(const GLfloat &a){
    return Vec2p5({(this->myVec[0] * a),(this->myVec[1] * a),(this->myVec[2] * a)});
}

vec3_2d::Vec2p5 vec3_2d::Vec2p5::operator+(const Vec2p5 &a){
    return Vec2p5({(this->myVec[0] + a.myVec[0]),(this->myVec[1] + a.myVec[1]),(this->myVec[2] + a.myVec[2])});
}
vec3_2d::Vec2p5 vec3_2d::Vec2p5::operator-(const Vec2p5 &a){
    return Vec2p5({(this->myVec[0] - a.myVec[0]),(this->myVec[1] - a.myVec[1]),(this->myVec[2] - a.myVec[2])});
}

GLboolean vec3_2d::Vec2p5::operator<(const GLfloat &a){
    return (GLboolean)(this->r < a);
}

GLboolean vec3_2d::Vec2p5::operator>(const GLfloat &a){
    return (GLboolean)(this->r > a);
}

GLboolean vec3_2d::Vec2p5::operator<=(const GLfloat &a){
    return (GLboolean)(this->r <= a);
}

GLboolean vec3_2d::Vec2p5::operator>=(const GLfloat &a){
    return (GLboolean)(this->r >= a);
}

GLboolean vec3_2d::Vec2p5::operator==(const GLfloat &a){
    return (GLboolean)(this->r == a);
}

std::vector<GLfloat> vec3_2d::Vec2p5::getVector(){
    return myVec;
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

void Triangle::build(std::vector<GLfloat> v_i){
    if(v_i.size() != 9)
    throw "Wrong vertex data";
    
    std::vector<std::vector<GLfloat>> v_s;

    a.push_back(v_i[0]);
    a.push_back(v_i[1]);
    a.push_back(v_i[2]);
    b.push_back(v_i[3]);
    b.push_back(v_i[4]);
    b.push_back(v_i[5]);
    c.push_back(v_i[6]);
    c.push_back(v_i[7]);
    c.push_back(v_i[8]);
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

GLfloat Triangle::getHeight(){
    return height;
}

GLfloat Triangle::getSide(){
    return side;
}

std::vector<GLfloat> Triangle::getA(){return a;}
std::vector<GLfloat> Triangle::getB(){return b;}
std::vector<GLfloat> Triangle::getC(){return c;}