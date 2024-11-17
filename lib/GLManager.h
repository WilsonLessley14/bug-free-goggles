#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#ifndef GLMANAGER
#define GLMANAGER

class GLManager {
  GLFWwindow* window;
  public:
  GLManager() {}
  ~GLManager() {}

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

  void setWindow(GLFWwindow* window) {
    this->window = window;
  }

  void processInput() {
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(this->window, true);
  }
};

#endif