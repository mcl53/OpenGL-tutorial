#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "shader.hpp"
#include "texture_structs.hpp"

class Mesh {

private:

    // Render data
    unsigned int VBO, EBO;

    void setupMesh();

public:

    unsigned int VAO;

    // Mesh data
    std::vector<Vertex>         vertices;
    std::vector<unsigned int>   indices;
    std::vector<Texture>        textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indeices, std::vector<Texture> textures);

    void draw(Shader &shader);

};

#endif