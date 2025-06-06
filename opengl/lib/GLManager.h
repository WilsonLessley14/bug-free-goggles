#ifndef GLMANAGER_H
#define GLMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class GLManager {
  GLFWwindow* window;

  public:
  GLManager() {}
  ~GLManager() {}

  static std::vector<bool> inputs;

  // -- callbacks -- //

  static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  }

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
      inputs[GLFW_KEY_W] = true;
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
      inputs[GLFW_KEY_W] = false;

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
      inputs[GLFW_KEY_S] = true;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
      inputs[GLFW_KEY_S] = false;
  }

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
    glfwSetKeyCallback(this->window, keyCallback);
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

std::vector<bool> GLManager::inputs(256, false);

#endif
