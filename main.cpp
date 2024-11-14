#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, char** argv) {
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
    std::cout << "Failed to create window" << std::endl;

    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // initialize GLAD
  // GLAD manages function pointers for OpenGL. we need to initialize it before calling any OpenGL function
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;

    glfwTerminate();
    return -1;
  }

  // defines the size of the rendering window (viewport)
  // this can be smaller than the window
  // first two ints are coords of the bottom left corner of the window
  // third and fourth are width and height, respectively
  glViewport(0, 0, 800, 600);

  // we want the viewport to resize with the window
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // note: callback functions must be registered after the window is created, but before the render loop is initiated

  // render loop initiated
  while(!glfwWindowShouldClose(window)) {
    // swaps the color buffer (large 2D buffer that contains color values for each pixel in the window)
    // shows this buffer as output
    // double buffering is a common method that avoids flickering when screens are drawn
    // we actually render to the "back" buffer
    // once rendering is complete, we swap the "back" buffer with the "front" buffer, so that the completed render is now being displayed
    glfwSwapBuffers(window);

    // checks for event triggers (keyboard input, mouse movement)
    // updates winodw state, and calls registered callback functions (when applicable)
    glfwPollEvents();
  }

  // gotta close your shit
  glfwTerminate();
  return 0;
}

// question - how do we know what parameters this function is going to be called with?
// does glfwSetFramebufferSizeCallback always invoke the callback with width and height? what else can it invoke with? do all callbacks get invoked the same way?
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}