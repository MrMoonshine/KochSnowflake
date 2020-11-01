#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#define INITIAL_FOV 45.0f
#define MOUSE_SPEED 0.005f
#define MOVEMENT_SPEED 3.0f

/*-----------------------------------------------
This class contains all necesary features
for input handling. 
-----------------------------------------------*/
class Input{
    private:
        void getWinDimensions();
        void centerCursor();
        GLfloat getRatio();
        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;
        glm::vec3 position;
        GLint height;
        GLint width;
        GLfloat horizontalAngle;
        GLfloat verticalAngle;
        GLFWwindow *window;
    public:
        Input(GLFWwindow *window_i);
        void checkMouse();
        void computeMatrices();
        glm::mat4 getViewMatrix();
        ::mat4 getProjectionMatrix();
        GLdouble mouseX;
        GLdouble mouseY;
};