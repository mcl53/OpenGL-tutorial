#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <iostream>

unsigned int loadTexture(const char* path);

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma);

void setTextureParameters();

#endif