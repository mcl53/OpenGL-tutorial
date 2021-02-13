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
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

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

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(-2.5f, 0.0f, -0.5f)
    };

    // load in texture
    setTextureParameters();
    
    unsigned int container = loadTexture("textures/container2.png");
    unsigned int containerSpecular = loadTexture("textures/container2_specular.png");

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

    // Setting texture shader constant variables
    textureShader.use();
    // Material
    textureShader.setInt("material.diffuse", 0);
    textureShader.setInt("material.specular", 1);
    textureShader.setFloat("material.shininess", 64.0f);
    // Directional light (the sun)
    textureShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    textureShader.setVec3("dirLight.ambient", glm::vec3(0.2f));
    textureShader.setVec3("dirLight.diffuse", glm::vec3(0.25f));
    textureShader.setVec3("dirLight.specular", glm::vec3(0.4f));
    // Point Lights (4 of)
    textureShader.setVec3("pointLights[0].position", pointLightPositions[0]);
    textureShader.setVec3("pointLights[1].position", pointLightPositions[1]);
    textureShader.setVec3("pointLights[2].position", pointLightPositions[2]);
    textureShader.setVec3("pointLights[3].position", pointLightPositions[3]);

    textureShader.setVec3("pointLights[0].ambient", glm::vec3(0.2f));
    textureShader.setVec3("pointLights[0].diffuse", glm::vec3(0.4f));
    textureShader.setVec3("pointLights[0].specular", glm::vec3(0.8f));
    textureShader.setVec3("pointLights[1].ambient", glm::vec3(0.2f));
    textureShader.setVec3("pointLights[1].diffuse", glm::vec3(0.4f));
    textureShader.setVec3("pointLights[1].specular", glm::vec3(0.8f));
    textureShader.setVec3("pointLights[2].ambient", glm::vec3(0.2f));
    textureShader.setVec3("pointLights[2].diffuse", glm::vec3(0.4f));
    textureShader.setVec3("pointLights[2].specular", glm::vec3(0.8f));
    textureShader.setVec3("pointLights[3].ambient", glm::vec3(0.2f));
    textureShader.setVec3("pointLights[3].diffuse", glm::vec3(0.4f));
    textureShader.setVec3("pointLights[3].specular", glm::vec3(0.8f));

    textureShader.setFloat("pointLights[0].constant", 1.0f);
    textureShader.setFloat("pointLights[0].linear", 0.022f);
    textureShader.setFloat("pointLights[0].quadratic", 0.0019f);
    textureShader.setFloat("pointLights[1].constant", 1.0f);
    textureShader.setFloat("pointLights[1].linear", 0.022f);
    textureShader.setFloat("pointLights[1].quadratic", 0.0019f);
    textureShader.setFloat("pointLights[2].constant", 1.0f);
    textureShader.setFloat("pointLights[2].linear", 0.022f);
    textureShader.setFloat("pointLights[2].quadratic", 0.0019f);
    textureShader.setFloat("pointLights[3].constant", 1.0f);
    textureShader.setFloat("pointLights[3].linear", 0.022f);
    textureShader.setFloat("pointLights[3].quadratic", 0.0019f);
    // Spotlight
    textureShader.setFloat("spotLight.cutoff", glm::cos(glm::radians(10.0f)));
    textureShader.setFloat("spotLight.outerCutoff", glm::cos(glm::radians(12.5f)));

    textureShader.setVec3("spotLight.ambient", glm::vec3(0.2f));
    textureShader.setVec3("spotLight.diffuse", glm::vec3(0.5f));
    textureShader.setVec3("spotLight.specular", glm::vec3(1.0f));

    textureShader.setFloat("spotLight.constant", 1.0f);
    textureShader.setFloat("spotLight.linear", 0.022f);
    textureShader.setFloat("spotLight.quadratic", 0.0019f);

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

        // Set vertex shader uniform variables
        textureShader.setMat4("projection", camera.getProjection());
        textureShader.setMat4("view", camera.getView());

        // Set fragment shader uniform variables
        textureShader.setVec3("spotLight.position", camera.cameraPos);
        textureShader.setVec3("spotLight.direction", camera.cameraFront);

        textureShader.setVec3("viewPos", camera.cameraPos);

        // Bind and draw cube object
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, container);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, containerSpecular);

        glBindVertexArray(VAO);
        // Container party
        for (int i = 0; i < 10; i++) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            textureShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Move and scale light object
        // glm::mat4 lightModel(1.0f);
        // lightModel = glm::translate(lightModel, lightPos);
        // lightModel = glm::scale(lightModel, glm::vec3(0.2f));

        // // Set shader uniform variables for the current frame for light object
        lightingShader.use();
        lightingShader.setVec3("lightColour", lightColour);
        lightingShader.setMat4("projection", camera.getProjection());
        lightingShader.setMat4("view", camera.getView());

        // Draw light objects
        glBindVertexArray(lightVAO);
        for (int i = 0; i < 4; i++) {
            glm::mat4 lightModel(1.0f);
            lightModel = glm::translate(lightModel, pointLightPositions[i]);
            lightModel = glm::scale(lightModel, glm::vec3(0.2f));
            lightingShader.setMat4("model", lightModel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Clear vertex array
        glBindVertexArray(0);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
