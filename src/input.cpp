#include <iostream>
#include <GLFW/glfw3.h>
#include "input.hpp"

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

float speed = 0.01;

void processArrowKey(GLFWwindow *window, translation &trans) {

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        trans.x -= speed;
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        trans.x += speed;
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        trans.y += speed;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        trans.y -= speed;
    } 
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        speed += 0.001;
        if (speed > 0.05f) {
            speed = 0.05f;
        }
    } else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        speed -= 0.001;
        if (speed < 0.001) {
            speed = 0.001;
        }
    }
}

void processChangeMixValue(GLFWwindow* window, float &currentMixValue) {
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        currentMixValue += 0.02;
        if (currentMixValue > 1.0) {
            currentMixValue = 1.0;
        }
    } else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        currentMixValue -= 0.02;
        if (currentMixValue < 0.0) {
            currentMixValue = 0.0;
        }
    }
}
