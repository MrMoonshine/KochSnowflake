#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader{
    private:
        void checkCompileErrors(GLuint shader_i, std::string name_i);
    public:
        Shader(std::string vertexPath,std::string fragmentPath);
        ~Shader();
        GLuint id;
        void use();  
        // utility uniform functions
        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;    
};

#endif