#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <test.hpp>
#include "shader.hpp"
#include "utils.hpp"
#include <stb/stb_image.h>

int main() {
    GLFWwindow* window = createOpenGLWindow(800, 600, (char*)"Test");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    Shader shaderProgram("src/shaders/vertex.txt", "src/shaders/fragment.txt");

    // Initialise state variables
    bool clicked = false;

    float vertices1[] = {
        // location       // colour
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    float textureCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };

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

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        // Get inputs
        processClose(window);
        processClick(window, clicked);
        processArrowKey(window, vertices1);
        glfwSetKeyCallback(window, processKeyPress);

        // Render to window
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
        
        glUseProgram(shaderProgram.id);
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