#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <input.hpp>
#include "shader.hpp"
#include "utils.hpp"
#include "textures.hpp"
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "camera.hpp"

int main() {
    int width = 800;
    int height = 600;

    GLFWwindow* window = createOpenGLWindow(width, height, (char*)"Test");
    glfwMakeContextCurrent(window);

    checkGLAD();

    glViewport(0, 0, width, height);

    //texture shader
    Shader textureShader("src/shaders/tex_vertex.txt", "src/shaders/tex_fragment.txt");

    //lighting shader
    Shader lightingShader("src/shaders/light_vertex.txt", "src/shaders/light_fragment.txt");

    // Initialise state variables
    bool clicked = false;

    float cubeVertices[] = {
        // vertices          //normals             //texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, 
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    };

    glm::vec3 lightPos(1.5f, 1.0f, 1.5f);

    // load in texture
    setTextureParameters();
    
    unsigned int container = loadTexture("textures/container2.png");

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s) and set vertex attribute(s)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_DYNAMIC_DRAW);

    // Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture Coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // Buffer the same coordinates for light - these will be translated to a different point in the scene later
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Define the colour of the light and the object (without textures)
    glm::vec3 lightColour(1.0f, 1.0f, 1.0f);
    // glm::vec3 objectColour(1.0f, 1.0f, 1.0f);

    textureShader.use();
    textureShader.setInt("material.diffuse", 0);
    textureShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    textureShader.setFloat("material.shininess", 64.0f);

    glm::mat4 projection(1.0f);
    float fov = 45.0f;

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    double xpos, ypos;


    Camera camera((float)width, (float)height, GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT, ((float)width)/2, ((float)height)/2, true, true);
    Camera* pCamera = &camera;
    glfwSetWindowUserPointer(window, pCamera);
    glfwSetKeyCallback(window, processKeyPress);
    glfwSetScrollCallback(window, processScroll);

    int modelLoc = glGetUniformLocation(textureShader.id, "model");
    int viewLoc = glGetUniformLocation(textureShader.id, "view");
    int projectionLoc = glGetUniformLocation(textureShader.id, "projection");

    int lightModelLoc = glGetUniformLocation(lightingShader.id, "model");
    int lightViewLoc = glGetUniformLocation(lightingShader.id, "view");
    int lightProjLoc = glGetUniformLocation(lightingShader.id, "projection");

    while (!glfwWindowShouldClose(window)) {
        // Time for this frame
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Get inputs
        processClose(window);
        processClick(window, clicked);
        glfwGetCursorPos(window, &xpos, &ypos);
        camera.movePosition(window, deltaTime);
        camera.moveDirection(window, xpos, ypos);
        camera.update();

        // Render to window
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        textureShader.use();

        glm::mat4 lightModel(1.0f);
        glm::vec3 lightTrans = glm::vec3(1.5 * glm::cos(currentFrame), 1.5f, 1.5 * glm::sin(currentFrame));

        // Set shader uniform variables for the current frame for cube object
        glm::mat4 model(1.0f);
        textureShader.setMat4("projection", camera.getProjection());
        textureShader.setMat4("view", camera.getView());
        textureShader.setMat4("model", model);
        textureShader.setVec3("viewPos", camera.cameraPos);
        textureShader.setVec3("light.lightPos", lightTrans);
        textureShader.setVec3("light.ambient", lightColour * glm::vec3(0.2f, 0.2f, 0.2f));
        textureShader.setVec3("light.diffuse", lightColour * glm::vec3(0.5f, 0.5f, 0.5f));
        textureShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        // Bind and draw cube object
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, container);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Move and scale light object
        lightModel = glm::translate(lightModel, lightTrans);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));

        // Set shader uniform variables for the current frame for light object
        lightingShader.use();
        lightingShader.setVec3("lightColour", lightColour);
        lightingShader.setMat4("projection", camera.getProjection());
        lightingShader.setMat4("view", camera.getView());
        lightingShader.setMat4("model", lightModel);

        // Draw light object
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Clear vertex array
        glBindVertexArray(0);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
