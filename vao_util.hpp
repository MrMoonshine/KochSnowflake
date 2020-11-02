#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class VAO {
    private:
        std::vector<GLfloat> arr2vec(GLfloat *ptr_i, GLuint size_i);
    protected:
        std::vector<GLfloat> buffer_vector;
        std::vector<Color> color_vector;
        std::vector<GLfloat> color_vector_float();
    public:
        VAO(std::vector<GLfloat> v_i);
        VAO(GLfloat *buffer_data_i,GLuint length_i);
        ~VAO();
        GLuint arrayID;
        GLuint buffer;
        GLuint colorbuffer;
        void build();
        void draw();
        void singleColor(Color color_i);
        void setColorbuffer(std::vector<Color> buff_i);
        void setColor();
        void showBuffers();
};