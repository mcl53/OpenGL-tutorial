#include <iostream>
#include <GLFW/glfw3.h>
#include "input.hpp"
#include <glm/glm.hpp>

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



void processArrowKey(GLFWwindow *window, glm::vec3 &cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float frameTime) {
    float speed = 2.0f * frameTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += speed * cameraFront;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= speed * cameraFront;
    } 
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        speed += 0.01;
        if (speed > 0.5f) {
            speed = 0.5f;
        }
    } else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        speed -= 0.01;
        if (speed < 0.01) {
            speed = 0.01;
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

void mouseInput(GLFWwindow* window, double xpos, double ypos, float &lastX, float &lastY, float &yaw, float &pitch) {
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0) {
        pitch = 89.0;
    } else if (pitch < -89.0) {
        pitch = -89.0;
    }
}

void processScroll(GLFWwindow* window, double xoffset, double yoffset) {
    void* vZoom = glfwGetWindowUserPointer(window);
    float* pZoom = {static_cast<float*>(vZoom)};
    *pZoom -= (float)yoffset;
    if (*pZoom < 1.0f) {
        *pZoom = 1.0f;
    } else if (*pZoom > 45.0f) {
        *pZoom = 45.0f;
    }
}