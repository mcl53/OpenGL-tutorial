#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include <assimp/scene.h>
#include "mesh.hpp"
#include "texture_structs.hpp"
#include "shader.hpp"

class Model {

private:

    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

public:

    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;

    Model(std::string const &path, bool gamma = false);
    void draw(Shader &shader);

};

#endif