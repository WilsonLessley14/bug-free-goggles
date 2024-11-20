#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* initializeGL(int width = 800, int height = 600);

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 vertexColor;\n"
"void main() {\n"
  "gl_Position = vec4(aPos, 1.0);\n"
  "vertexColor = aColor;\n"
"}\n";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
"void main() {\n"
  "FragColor = vec4(vertexColor, 1.0);\n"
"}\n";

int main(int argc, char** argv) {
  GLFWwindow* window = initializeGL();

  unsigned int vertexShader, fragmentShader[2];
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShader[0], 1, &fragmentShaderSource, NULL);
  glCompileShader(vertexShader);
  glCompileShader(fragmentShader[0]);

  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "error! vertex shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  unsigned int shaderProgram[2];
  shaderProgram[0] = glCreateProgram();

  glAttachShader(shaderProgram[0], vertexShader);
  glAttachShader(shaderProgram[0], fragmentShader[0]);

  glLinkProgram(shaderProgram[0]);

  glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgram[0], 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader[0]);

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

  while(!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram[0]);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, VAO);
  glDeleteBuffers(1, VBO);
  glDeleteProgram(shaderProgram[0]);

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

GLFWwindow* initializeGL(int width, int height) {
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

  return window;
}
