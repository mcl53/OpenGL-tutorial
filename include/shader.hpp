#ifndef SHADER_H
#define SHADER_H

#include <iostream>

class Shader {

public:
    // program ID
    unsigned int id;

    // constructor to read shaders from file and build them
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    void use();
    // utility uniform functions
    const void setBool(const std::string &name, bool value);
    const void setInt(const std::string &name, int value);
    const void setFloat(const std::string &name, float value);

};

#endif