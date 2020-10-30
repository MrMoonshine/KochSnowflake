#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "shader.hpp"
#define ERR_MSG_BUFF_SIZE 1024

void Shader::checkCompileErrors(GLuint shader_i, std::string name_i){
    GLint success;
    GLchar infolog[ERR_MSG_BUFF_SIZE];

    if(name_i != "PROGRAM"){
        glGetProgramiv(shader_i,GL_COMPILE_STATUS,&success);
        if(!success){
            glGetShaderInfoLog(shader_i, ERR_MSG_BUFF_SIZE, NULL, infolog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << name_i << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }else{
        glGetProgramiv(shader_i,GL_LINK_STATUS,&success);
        if(!success){
            glGetShaderInfoLog(shader_i, ERR_MSG_BUFF_SIZE, NULL, infolog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << name_i << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::Shader(std::string vertexPath,std::string fragmentPath){
    //Retrive shader source code
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try{
        //open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStraem, fShaderStream;

        //read file buffer contents into streams
        vShaderStraem << vShaderFile.rdbuf();
        fShaderStream << vShaderFile.rdbuf();

        //close file handlers
        vShaderFile.close();
        fShaderFile.close();

        //stream to string
        vertexCode = vShaderStraem.str();
        fragmentCode = fShaderStream.str();   

    }catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    //Compile shaders!
        GLuint vertex, fragment;
        GLint success;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&vShaderCode,NULL);
        glCompileShader(vertex);

        // print compile errors if any
        checkCompileErrors(id,"VERTEX");

        //Do the same for the Fragmentshader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&fShaderCode,NULL);
        glCompileShader(fragment);

        // print compile errors if any
        checkCompileErrors(id,"FRAGMENT");

        //Create shader Programm
        id = glCreateProgram();
        glAttachShader(id,vertex);
        glAttachShader(id,fragment);
        glLinkProgram(id);
        //Again check for errors
        checkCompileErrors(id,"PROGRAM");

        glDetachShader(id,vertex);
        glDetachShader(id,fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader(){
    glDeleteProgram(id);
    //std::cout << "Deleted Shader" << std::endl;
}

void Shader::use(){
    glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const{         
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const{ 
    glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const{ 
    glUniform1f(glGetUniformLocation(id, name.c_str()), value); 
} 