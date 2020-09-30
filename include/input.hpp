void processClose(GLFWwindow* window);

void processClick(GLFWwindow* window, bool &currentlyClicked);

void processKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);

void processArrowKey(GLFWwindow* window, float* vertices, int valuesPerVertex, int verticesSize);

void processChangeMixValue(GLFWwindow* window, float &currentMixValue);
