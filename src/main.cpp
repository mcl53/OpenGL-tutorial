#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <test.hpp>
#include <cmath>

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColour;\n"
    "out vec3 drawColour;\n"
    "void main() {\n"
    "  gl_Position = vec4(aPos, 1.0f);\n"
    "  drawColour = aColour;\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColour;\n"
    "in vec3 drawColour;\n"
    "void main() {\n"
    "  FragColour = vec4(drawColour, 1.0f);\n"
    "}\0";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << std::endl;
    } 
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Initialise state variables
    bool clicked = false;

    float vertices1[] = {
        // location       // colour
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    // float vertices2[] = {
    //     0.5f, 0.5f, 0.0f,
    //     0.0f, 0.0f, 0.0f,
    //     0.0f, 0.5f, 0.0f
    // };

    // unsigned int indices[] = {
    //     0, 1, 2,
    // };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s) and set vertex attribute(s)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glBindVertexArray(VAO[1]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        // Get inputs
        processClose(window);
        processClick(window, clicked);
        processArrowKey(window, vertices1);
        glfwSetKeyCallback(window, processKeyPress);

        // Rebuffer data if it has been changed
        // glBindVertexArray(VAO[0]);
        // glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_DYNAMIC_DRAW);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        // glEnableVertexAttribArray(0);
        

        // Render to window
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glUseProgram(shaderProgramOrange);
        // glBindVertexArray(VAO[1]);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}