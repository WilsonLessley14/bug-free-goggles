#ifndef GLMANAGER_H
#define GLMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


// -- callbacks -- //

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

class GLManager {
  GLFWwindow* window;

  public:
  GLManager() {}
  ~GLManager() {}

  // -- getting functions -- //

  GLFWwindow* getWindow() {
    return this->window;
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

  GLFWwindow* initializeGL(int width = 800, int height = 600) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
      glfwTerminate();
      throw ("Failed to create window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      glfwTerminate();
      throw ("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    this->setWindow(window);

    return window;
  }

};


#endif