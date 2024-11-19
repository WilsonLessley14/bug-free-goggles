#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* initializeGL(int width = 800, int height = 600);

const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragmentShadrOrangeSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

const char *fragmentShadrYellowSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n";

int main(int argc, char** argv) {
  GLFWwindow* window = initializeGL();

  unsigned int vertexShader, fragmentShader[2];
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
  fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShader[0], 1, &fragmentShadrOrangeSource, NULL);
  glShaderSource(fragmentShader[1], 1, &fragmentShadrYellowSource, NULL);
  glCompileShader(vertexShader);
  glCompileShader(fragmentShader[0]);
  glCompileShader(fragmentShader[1]);

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
  shaderProgram[1] = glCreateProgram();

  glAttachShader(shaderProgram[0], vertexShader);
  glAttachShader(shaderProgram[0], fragmentShader[0]);

  glAttachShader(shaderProgram[1], vertexShader);
  glAttachShader(shaderProgram[1], fragmentShader[1]);

  glLinkProgram(shaderProgram[0]);
  glLinkProgram(shaderProgram[1]);

  glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgram[0], 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgram[1], 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader[0]);
  glDeleteShader(fragmentShader[1]);

  float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    -0.25f, 0.5f, 0.0f,
    0.25f, 0.5f, 0.0f,
  };

  unsigned int indices[] = {
    2, 4, 5,
    1, 4, 6,
  };

  float rightTriangle[] = {
    0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.25f, 0.5f, 0.0f,
  };

  float leftTriangle[] = {
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    -0.25f, 0.5f, 0.0f,
  };

  unsigned int EBO, VBO[2], VAO[2];
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(rightTriangle), rightTriangle, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(leftTriangle), leftTriangle, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while(!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram[0]);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram[1]);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);
  glDeleteProgram(shaderProgram[0]);
  glDeleteProgram(shaderProgram[1]);

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
