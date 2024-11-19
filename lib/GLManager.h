#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#ifndef GLMANAGER
#define GLMANAGER

class GLManager {
  GLFWwindow* window;

  unsigned int VAO[5];
  unsigned int VBO[5];
  unsigned int EBO[5];

  public:
  GLManager() {}
  ~GLManager() {}

  // -- getting functions -- //

  GLFWwindow* getWindow() {
    return this->window;
  }

  unsigned int* getVAO() {
    return this->VAO;
  }

  unsigned int* getVBO() {
    return this->VBO;
  }

  unsigned int* getEBO() {
    return this->EBO;
  }

  // -- setting functions -- //

  void setWindow(GLFWwindow* window) {
    this->window = window;
  }

  // -- action functions -- //

  void processInput() {
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(this->window, true);
  }

  GLFWwindow* generateWindow() {
    //instantiate the glfw window
    glfwInit();

    // using OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // use coreprofile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // for macOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
      throw("Failed to create window");
      glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // set the GLmanagers window pointer
    this->setWindow(window);
    return window;
  }


};

#endif