#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
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
    // positions          // colors
    0.5f, -0.5f,  0.0f,   1.0f,  0.0f,  0.0f, // bottom right
   -0.5f, -0.5f,  0.0f,   0.0f,  1.0f,  0.0f, // bottom left
    0.0f,  0.5f,  0.0f,   0.0f,  0.0f,  1.0f, // top middle
  };

  unsigned int VBO[2], VAO[2];
  glGenVertexArrays(1, VAO);
  glGenBuffers(1, VBO);

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // stride is 6 floats. first 3 are position values, next 3 are color values
  // start at position 0, move 6 at a time
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // start at position 3, move 6 at a time
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  //textures
  int width, height, channelsCount;
  unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &channelsCount, 0);

  unsigned int texture;
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

  while(!glfwWindowShouldClose(window)) {
    manager.processInput();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    shader.setFloat("offsetX", 0.5f);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, VAO);
  glDeleteBuffers(1, VBO);

  glfwTerminate();
  return 0;
}
