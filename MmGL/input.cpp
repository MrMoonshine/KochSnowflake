#include <iostream>
#include <string>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;
#include "input.hpp"

Input::Input(GLFWwindow *window_i){
    window = window_i;
    getWinDimensions();
    //Set initial view angle
    horizontalAngle = M_PI;
    verticalAngle = 0.0f;

    // Initial position : on +Z
    position = glm::vec3( 0, 0, 5 ); 
}

void Input::checkMouse(){
    glfwGetCursorPos(window,&mouseX,&mouseY);
    //std::cout << "X Y: " << mouseX << " " << mouseY << std::endl;
}

void Input::centerCursor(){
    getWinDimensions();
    glfwSetCursorPos(window,width/2,height/2);
}

void Input::computeMatrices(){
    //This will calculate the time between the current and the last
    //frame. And therefore the framerate
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();

    if(lastTime == 0 || currentTime == 0)
    std::cout << "GLFW-Timer Error occured!" << std::endl;

    float deltaTime = float(currentTime - lastTime);

    //get current mouse position to calculate
    //the new orientation
    checkMouse();
    //Center Mouse
    centerCursor();

    //calculate new orientation
    //mouseSpeed * offset from center
    horizontalAngle += MOUSE_SPEED * float(width/2 - mouseX);
    verticalAngle += MOUSE_SPEED * float(height/2 - mouseY);

    //Spherical to Cartesian coordinates
    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    //Right vector
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - M_PI / 2.0f),
        0,
        cos(horizontalAngle - M_PI / 2.0f)
    );

    //Up vector
    glm::vec3 up = glm::cross(right,direction);

    //Movement!
    //It's a Minecraft-Like control therefore: W,A,S,D
    //Forward
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
    position += direction * deltaTime * MOVEMENT_SPEED;
    //backward
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    position -= direction * deltaTime * MOVEMENT_SPEED;
    //strafe right
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    position += right * deltaTime * MOVEMENT_SPEED;
    //strafe left
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    position -= right * deltaTime * MOVEMENT_SPEED;

    //fly up
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
    position += up * deltaTime * MOVEMENT_SPEED;
    //fly down
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    position -= up * deltaTime * MOVEMENT_SPEED;

    //Field of view (FOV)
    static GLfloat FoV = INITIAL_FOV;

    // Projection matrix : 45� Field of View, ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(glm::radians(FoV),getRatio(),0.1f,100.0f);

    //Camera Matrix
    ViewMatrix = glm::lookAt(
        position,
        position + direction,
        up
    );
    lastTime = currentTime;
}

void Input::getWinDimensions(){
    glfwGetWindowSize(window,&width,&height);
    //std::cout << "width height: " << width << " " << height << std::endl;
}

GLfloat Input::getRatio(){
    return (GLfloat)width/(GLfloat)height;
}

glm::mat4 Input::getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 Input::getProjectionMatrix(){
	return ProjectionMatrix;
}