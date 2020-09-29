#include "shader.hpp"
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    
    // Retrieve the shader source code from filepath
    std::string vShaderString;
    std::string fShaderString;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // read shaders from file and store as char*
    try {
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vShaderString = vShaderStream.str();
        fShaderString = fShaderStream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        std::cout << e.what() << std::endl;
    }

    const char* vShaderSource = vShaderString.c_str();
    const char* fShaderSource = fShaderString.c_str();

    // compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderSource, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderSource, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(id);
}

const void Shader::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

const void Shader::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

const void Shader::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}