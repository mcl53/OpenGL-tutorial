struct translation {
    float x;
    float y;
};

void processClose(GLFWwindow* window);

void processClick(GLFWwindow* window, bool &currentlyClicked);

void processKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);

void processArrowKey(GLFWwindow* window, translation &trans);

void processChangeMixValue(GLFWwindow* window, float &currentMixValue);