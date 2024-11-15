#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// resizing window callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// processing inputs
void processInput(GLFWwindow *window);

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

  // 2d triangle defined with 3d coords
  float vertices[] = {
    -0.5f, -0.5f, 0,
    0.5f, -0.5f, 0,
    0.0f, 0.5f, 0,
  };

  // Normalized Device Coordinates (NDC)
  /*
    xyz values range from -1.0 to 1.0
    any coords outside of this range will be discarded/clipped
    0, 0 is direct center, and raising y moves up, not down (as opposed to typical graphics on computers)
    NDC coords get transformed into screen-space coordinates via `viewport transform` using data provided to glViewport
    screen-space coordinates are transformed to fragments as inputs to the fragment shader
  */

  /*
    we use vertex buffer objects to store a large number of vertices in GPU's memory
    we do this so that we can send large batches of data at once
    GPU takes time to recieve inputs, so the larger the batches the better.
  */

  // create buffer object
  unsigned int VBO;
  // generate/link buffer object within OpenGL context
  glGenBuffers(1, &VBO);
  // bind buffer object as the GL_ARRAY_BUFFER
  // many buffers can be assigned, as long as each has a different buffer type
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // glBufferData copies arg 3 into arg 1
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  /*
    GL_STREAM_DRAW: data set once and used by GPU a few times (at most)
    GL_STATIC_DRAW: data set once and used by GPU many times
    GL_DYNAMIC_DRAW: data is changed a lot and used many times
  */

  /* -------- Shader Sources -------- */

  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
      "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

  const char *fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n";

  /* -------- End Shader Sources -------- */

  /* -------- Shader Compilation -------- */

  // OpenGL has to compile the shader at run-time from it's own source code
  unsigned int vertexShader, fragmentShader;

  // store the shader as an unsigned int create the shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // attach shader source code to the shader object
  // shader object to compile, number of strings being passed as source code, shader source code, NULL
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  // compile the shader
  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // adding a debug statement. we are going to check if glCompileShader is succesful or not.
  // this is how we check for compile time errors

  // nice, no errors

  // integer that indicates success
  int success;
  char infoLog[512];

  // -- check for vertex shader compilation errors -- //
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "error! vertex shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  // -- check for fragment shader compilation errors -- //
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  /* -------- End Shader Compilation -------- */

  /* -------- Shader Program Creation, Attachment, and Linking -------- */

  // define the shader program
  unsigned int shaderProgram;
  // glCreateProgram creates the program object and returns the ID reference to this object
  shaderProgram = glCreateProgram();

  // attach previously compiled shaders to shader program
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  // link the program (with the shaders attached)
  glLinkProgram(shaderProgram);

  // -- check for linking errors -- //
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }


  /* -------- End Shader Program Creation, Attachment, and Linking -------- */


  // render loop initiated
  while(!glfwWindowShouldClose(window)) {

    // input processing phase
    processInput(window);

    // rendering phase

    // state setting function that specifies a color to "clear" the color buffer with
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // state using function that "clears" the color buffer with the previously set color value
    // we also have access to other buffers, like GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT
    // ultimately these two lines result in the window have a green blueish color
    glClear(GL_COLOR_BUFFER_BIT);

    // event polling phase
    // checks for event triggers (keyboard input, mouse movement)
    // updates winodw state, and calls registered callback functions (when applicable)
    glfwPollEvents();

    // swaps the color buffer (large 2D buffer that contains color values for each pixel in the window)
    // shows this buffer as output
    // double buffering is a common method that avoids flickering when screens are drawn
    // we actually render to the "back" buffer
    // once rendering is complete, we swap the "back" buffer with the "front" buffer, so that the completed render is now being displayed
    glfwSwapBuffers(window);
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

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
