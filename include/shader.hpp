#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <glm/glm.hpp>

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
    const void setMat4(const std::string &name, const glm::mat4 &value);
    const void setVec3(const std::string &name, const glm::vec3 &value);

};

#endif