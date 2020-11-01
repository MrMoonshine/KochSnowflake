#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

class Color{
    public:
    Color(GLfloat r,GLfloat g, GLfloat b, GLfloat alpha = 0.0f);
    ~Color();
    GLfloat red;
    GLfloat blue;
    GLfloat green;
    GLfloat alpha;
};

class MyGlfwUtil {
    private:
        std::string window_title;
    public:
        MyGlfwUtil(std::string title_i = "GLFW Window");
        ~MyGlfwUtil();
        GLFWwindow* window;
        void create(GLuint width = 640, GLuint height = 480);
        GLenum initGlew();
        void createHints();
        void makeContextCurrent();
        void setBackgroundColor(GLfloat r,GLfloat g, GLfloat b, GLfloat alpha = 0);
        void setBackgroundColor(Color color);
        void clear();
};