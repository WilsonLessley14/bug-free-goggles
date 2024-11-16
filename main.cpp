#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// resizing window callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// processing inputs
void processInput(GLFWwindow *window);

// shader sources
const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragmentShaderOrangeSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

const char *fragmentShaderYellowSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n";

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

  /* -------- Shader Compilation -------- */

  // OpenGL has to compile the shader at run-time from it's own source code
  unsigned int vertexShader, fragmentShaderOrange, fragmentShaderYellow;

  // store the shader as an unsigned int create the shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
  fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);

  // attach shader source code to the shader object
  // args; shader object to compile, number of strings being passed as source code, shader source code, NULL
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShaderOrange, 1, &fragmentShaderOrangeSource, NULL);
  glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
  glCompileShader(vertexShader);
  glCompileShader(fragmentShaderOrange);
  glCompileShader(fragmentShaderYellow);

  // this is how we check for compile time errors
  int success;
  char infoLog[512];

  // -- check for vertex shader compilation errors -- //
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "error! vertex shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  // -- check for fragment shader orange compilation errors -- //
  glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  // -- check for fragment shader yellow compilation errors -- //
  glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  /* -------- Shader Program Creation, Attachment, and Linking -------- */

  // define the shader program
  unsigned int shaderProgramOrange = glCreateProgram();
  unsigned int shaderProgramYellow = glCreateProgram();

  // attach previously compiled shaders to shader program
  glAttachShader(shaderProgramOrange, vertexShader);
  glAttachShader(shaderProgramOrange, fragmentShaderOrange);

  glAttachShader(shaderProgramYellow, vertexShader);
  glAttachShader(shaderProgramYellow, fragmentShaderYellow);

  // link the program (with the shaders attached)
  glLinkProgram(shaderProgramOrange);
  glLinkProgram(shaderProgramYellow);

  // -- check for linking errors -- //
  glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgramOrange, 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  // -- check for linking errors -- //
  glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgramYellow, 512, NULL, infoLog);
    std::cout << "error! fragment shader compilation failed.\nhere is the log: " << infoLog << std::endl;
  }

  // delete shaders once you are done with them
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShaderOrange);
  glDeleteShader(fragmentShaderYellow);

  /* -------- End Shader Program Creation, Attachment, and Linking -------- */

  // 2d triangle defined with 3d coords
  float vertices[] = {
    0.5f, 0.5f, 0.0f,     // top right      0
    0.5f, -0.5f, 0.0f,    // bottom right   1
    -0.5f, -0.5f, 0.0f,   // bottom left    2
    -0.5f, 0.5f, 0.0f,    // top left       3
    0.0f, -0.5f, 0.0f,    // bottom middle  4
    -0.25f, 0.5f, 0.0f,   // left peak      5
    0.25f, 0.5f, 0.0f,    // right peak     6
  };

  // EBO - element buffer object
  unsigned int indices[] = {
    2, 4, 5, // first triangle
    1, 4, 6, // second triangle
  };

  float rightTriangle[] = {
    0.5f, -0.5f, 0.0f,    // top right      1
    0.0f, -0.5f, 0.0f,    // bottom middle  4
    0.25f, 0.5f, 0.0f,    // right peak     6
  };

  float leftTriangle[] = {
    -0.5f, -0.5f, 0.0f,   // bottom left    2
    0.0f, -0.5f, 0.0f,    // bottom middle  4
    -0.25f, 0.5f, 0.0f,   // left peak      5
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

    Vertex Array Object, or VAO, can be bound just like a VBO.
    subsequent vertex attribute calls will be stored inside the VAO.

    aside: what is a vertex attribute?
    https://www.reddit.com/r/opengl/comments/91jcnf/what_is_a_vertex_attribute_in_opengl/
    good explanations in this forum
  */

  unsigned int EBO, VBOLeft, VBORight, VAOLeft, VAORight;

  // generate/link buffer and array objects within OpenGL context
  glGenVertexArrays(1, &VAORight);
  glGenVertexArrays(1, &VAOLeft);
  glGenBuffers(1, &VBORight);
  glGenBuffers(1, &VBOLeft);
  //glGenBuffers(1, &EBO);

  // bind the array object first
  glBindVertexArray(VAORight);
  // bind buffer object as the GL_ARRAY_BUFFER
  glBindBuffer(GL_ARRAY_BUFFER, VBORight);
  // glBufferData copies arg 3 into arg 1
  glBufferData(GL_ARRAY_BUFFER, sizeof(rightTriangle), rightTriangle, GL_STATIC_DRAW);

  // registering vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // bind element buffer object
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(VAOLeft);
  glBindBuffer(GL_ARRAY_BUFFER, VBOLeft);
  glBufferData(GL_ARRAY_BUFFER, sizeof(leftTriangle), leftTriangle, GL_STATIC_DRAW);


  /*
    GL_STREAM_DRAW: data set once and used by GPU a few times (at most)
    GL_STATIC_DRAW: data set once and used by GPU many times
    GL_DYNAMIC_DRAW: data is changed a lot and used many times
  */

  /* -------- Linking Vertex Attributes -------- */

  /* notes */
  /*
    position data is stored as 4 byte (32 bits) floating point values
    each position is composed of 3 floats
    values are tightly packed (no other information stored between each value)
    first value is at the beginning of the buffer
  */

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // lets walk through the above function invocation
  /*
    param 1:
      value: 0
      specifies which vertex attribute we want to configure.
      we specified the location of the `position` vertex attribute in the vertex shader with `layout (location=0)`
      this sets the location of the vertex attribute to 0
      since we want to pass data to this attribute, we pass in 0

    param 2:
      value: 3
      size of the vertex attribute.
      attribute is defined as vec3, so it's composed of 3 values

    param 3:
      value: GL_FLOAT
      specifies type of the data

    param 4:
      value: GL_FALSE
      specifies if we want the data to be normalized
      if we were inputing integer data types, we would set this to be GL_TRUE

    param 5:
      value: 3 * sizeof(float)
      refered to as the 'stride'
      tells us the space between consecutive vertex attributes
      each vertex is 3 floats, so the stride will be the size of 3 floats
      we could set this as 0, which lets openGL determine the stride (this only works when values are tightly packed) //try this
      when we have more vertex attributes, we need to carefully define the spacing between each vertex attribute

    param 6:
      value: (void*)0
      this last param is of type `void`, thus the weird cast here?
      this is the offest of where the position data begins in the buffer.
      this is 0 because our vertex object starts with position data


    glEnableVertexAttribArray uses the VBO that is bound to GL_ARRAY_BUFFER

  */

  // we are giving this function the vertex attribute location, so 0
  glEnableVertexAttribArray(0);

  // unbind VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // unbind VAO
  glBindVertexArray(0);

  /* -------- End Linking Vertex Attributes -------- */

  // render loop initiated
  while(!glfwWindowShouldClose(window)) {

    // --- INPUT --- //
    processInput(window);

    // --- RENDER --- //

    // uncomment next line for wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // state setting function that specifies a color to "clear" the color buffer with
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // state using function that "clears" the color buffer with the previously set color value
    // we also have access to other buffers, like GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT
    // ultimately these two lines result in the window have a green blueish color
    glClear(GL_COLOR_BUFFER_BIT);

    // bind shader program
    glUseProgram(shaderProgramOrange);
    // bind VAORight
    glBindVertexArray(VAORight);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramYellow);
    //bind VAOLeft
    glBindVertexArray(VAOLeft);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // unbind VAO
    glBindVertexArray(0);

    // swap buffers and poll IO events (keys pressed/released, mouse moved, etc.)
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  // de allocate resources
  glDeleteVertexArrays(1, &VAOLeft);
  glDeleteVertexArrays(1, &VAORight);
  glDeleteBuffers(1, &VBOLeft);
  glDeleteBuffers(1, &VBORight);
  glDeleteProgram(shaderProgramOrange);
  glDeleteProgram(shaderProgramYellow);

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
