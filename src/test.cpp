#include <iostream>
#include <GLFW/glfw3.h>

void processClose(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void processClick(GLFWwindow *window, bool &currentlyClicked) {
    if (currentlyClicked) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            std::cout << "Mouse clicked" << std::endl;
            currentlyClicked = false;
        }
    } else {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            currentlyClicked = true;
        }
    }
}

void processKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
        std::cout << "Pressed 1 key" << std::endl;
    }
}

void processArrowKey(GLFWwindow *window, float *vertices) {
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        std::cout << "Left key pressed" << std::endl;
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) {
                vertices[i] -= 0.001;
            }
        }
    }
}