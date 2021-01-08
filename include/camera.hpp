#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {

public:

    Camera(float screenWidth, float screenHeight, int forward, int back, int left, int right, int up, int down, float mouseStartX, float mouseStartY, bool constrainPitch, bool fpsStyle);

    void movePosition(GLFWwindow *window, float frameTime);
    void moveDirection(GLFWwindow* window, double xpos, double ypos);
    void zoom(double xoffset, double yoffset);
    void update();
    glm::mat4 getProjection();
    glm::mat4 getView();

// private:
    int forwardKey, backKey, leftKey, rightKey, upKey, downKey;
    bool pitchConstrained, fps;
    float width, height;
    double xpos, ypos;

    bool firstMouse;

    float yaw;
    float pitch;
    float lastX;
    float lastY;
    float zoomValue;

    float fov;
    float speed;
    float sensitivity;
    
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    glm::mat4 view;
    glm::mat4 projection;

    void updateCameraFront();
    void updateProjection();
    void updateView();

};

#endif