#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "lib/GLManager.h"
#include "lib/Shader.h"


const char *vertexShaderPath = "./shaders/shader.vs";

const char *fragmentShaderPath = "shaders/shader.fs";

int main(int argc, char** argv) {
  GLManager manager = GLManager();
  GLFWwindow* window = manager.initializeGL();
  Shader shader = Shader(vertexShaderPath, fragmentShaderPath);

  float vertices[] = {
    // positions          // colors             // texture coords
    0.5f,  0.5f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,  // top right
    0.5f, -0.5f,  0.0f,   0.0f,  1.0f,  0.0f,   1.0f,  0.0f,  // bottom right
   -0.5f, -0.5f,  0.0f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  // bottom left
   -0.5f,  0.5f,  0.0f,   1.0f,  1.0f,  0.0f,   0.0f,  1.0f,  // top left
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  unsigned int VBO[2], VAO[2], EBO;
  glGenVertexArrays(1, VAO);
  glGenBuffers(1, VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // stride is 8 floats. first 3 are position values, next 3 are color values, next 2 are texture coords
  // start at position 0, move 8 at a time
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // start at position 3, move 8 at a time
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // start at position 6, move 8 at a time
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  //textures
  unsigned int texture[2];
  glGenTextures(2, texture);
  glBindTexture(GL_TEXTURE_2D, texture[0]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, texture[0]);

  int width, height, channelsCount;

  // OGL expects y = 0 to be on the bottom, but most image files treat y = 0 to be the top
  // this flag flips y axis during image load
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &channelsCount, 0);
  if (!data) {
    std::cout << "Failed to load texture" << std::endl;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture[1]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // both textures render w/o freeing data between texture loads
  // but I think this is best practice. don't want to get in the habit of loading some data where other data already exists
  stbi_image_free(data);
  data = stbi_load("textures/awesomeface.png", &width, &height, &channelsCount, 0);
  if (!data) {
    std::cout << "Failed to load texture" << std::endl;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

  glBindTexture(GL_TEXTURE_2D, 0);

  shader.use();
  // need to tell the shader program about any shader used above shader 0
  shader.setInt("texture1", 1);
  //uncomment next line for wireframe mode:
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  float opacity = 0.2f;
  while(!glfwWindowShouldClose(window)) {
    manager.processInput();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (GLManager::inputs[GLFW_KEY_W])
      opacity += 0.1f;
    if (GLManager::inputs[GLFW_KEY_S])
      opacity -= 0.1f;

    shader.setFloat("opacity", opacity);

    // might be best practice to activate and bind texture 0 here, but it does not seem technically necessary
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    
    float time = glfwGetTime();

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.5f));
    trans = glm::rotate(trans, time, glm::vec3(0.0f, 0.0f, 1.0f));

    shader.setMat4("transform", trans);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    trans = glm::mat4(1.0f);

    trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, -0.5f));
    trans = glm::scale(trans, glm::vec3(sin(time), abs(sin(time)), 0.0f));

    shader.setMat4("transform", trans);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, VAO);
  glDeleteBuffers(1, VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
  return 0;
}
