#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <input.hpp>
#include "shader.hpp"
#include "utils.hpp"
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

int main() {
    GLFWwindow* window = createOpenGLWindow(800, 600, (char*)"Test");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    float textureMixValue = 0.5f;

    Shader shaderProgram("src/shaders/vertex.txt", "src/shaders/fragment.txt");
    shaderProgram.setFloat("textureMix", textureMixValue);

    // Initialise state variables
    bool clicked = false;

    float vertices1[] = {
        // location       // colour         // texture coords
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f // bottom right
    };

    int sizeOfVertices = sizeof(vertices1) / sizeof(vertices1[0]);

    float textureCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };

    // load in texture
    stbi_set_flip_vertically_on_load(true);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int tWidth, tHeight, tNrChannels;
    unsigned int container, awesomeface;
    unsigned char* containerData = stbi_load("textures/container.jpg", &tWidth, &tHeight, &tNrChannels, 0);
    if (containerData) {
        glGenTextures(1, &container);
        glBindTexture(GL_TEXTURE_2D, container);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, containerData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(containerData);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    unsigned char* awesomefaceData = stbi_load("textures/awesomeface.png", &tWidth, &tHeight, &tNrChannels, 0);
    if (awesomefaceData) {
        glGenTextures(1, &awesomeface);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomeface);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, awesomefaceData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s) and set vertex attribute(s)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shaderProgram.use();
    shaderProgram.setInt("containerTex", 0);
    shaderProgram.setInt("awesomefaceTex", 1);
    
    translation boxTrans;
    boxTrans.x = 0.0f;
    boxTrans.y = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        // Get inputs
        processClose(window);
        processClick(window, clicked);
        processArrowKey(window, boxTrans);
        processChangeMixValue(window, textureMixValue);
        glfwSetKeyCallback(window, processKeyPress);
        shaderProgram.setFloat("textureMix", textureMixValue);

        // Render to window
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(boxTrans.x, boxTrans.y, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        unsigned int transformLocation = glGetUniformLocation(shaderProgram.id, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, container);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomeface);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glm::mat4 trans2(1.0f);
        trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans2 = glm::scale(trans2, glm::vec3(abs(sin((float)glfwGetTime())), abs(sin((float)glfwGetTime())), 1.0f));
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans2));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}