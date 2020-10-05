#include <glm/glm.hpp>

void processClose(GLFWwindow* window);

void processClick(GLFWwindow* window, bool &currentlyClicked);

void processKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);

void processArrowKey(GLFWwindow *window, glm::vec3 &cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float frameTime);

void processChangeMixValue(GLFWwindow* window, float &currentMixValue);

void mouseInputWrapper(GLFWwindow* window, double xpos, double ypos);

void mouseInput(GLFWwindow* window, double xpos, double ypos, float &lastX, float &lastY, float &yaw, float &pitch);

void processScroll(GLFWwindow* window, double xoffset, double yoffset);