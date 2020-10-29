#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class VAO {
    private:
        GLuint buffer_size = 0;
        std::vector<Color> color_vector;
        std::vector<GLfloat> color_vector_float();
    public:
        VAO(GLfloat *buffer_data_i,GLuint length_i);
        ~VAO();
        GLuint arrayID;
        GLuint buffer;
        GLfloat *buffer_data;
        GLuint colorbuffer;
        void build();
        void draw();
        void setColorbuffer(std::vector<Color> buff_i);
        void setColor();
};