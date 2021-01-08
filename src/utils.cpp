#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.hpp"

GLFWwindow* createOpenGLWindow(int width, int height, char* name) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    } else {
        return window;
    }
}

void checkGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // std::cout << "Failed to initialise GLAD" << std::endl;
        throw std::runtime_error("Failed to initialise GLAD");
    }
}
