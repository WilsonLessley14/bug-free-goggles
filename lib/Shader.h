#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {

  //for debugging
  int success;
  char infoLog[512];

  std::string readShaderFromFile(const char* shaderPath) {
    std::string shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
      //open files
      shaderFile.open(shaderPath);

      std::stringstream shaderStream;

      // read the file buffer contents into streams
      shaderStream << shaderFile.rdbuf();

      shaderFile.close();

      shaderCode = shaderStream.str();
    } catch(std::ifstream::failure e) {
      std::cout << "error reading shader from file" << std::endl;
    }
    return shaderCode;
  }

  void compileShader(const char* shaderCode, unsigned int &shaderID) {
    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success) {
      glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
      std::cout << "error shader compilation failed. log: " << infoLog << std::endl;
    }

    glAttachShader(ID, shaderID);
  }

 public:

  // program id?
  unsigned int ID;

  // -- Method Definitions -- //
  Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = readShaderFromFile(vertexPath);
    std::string fragmentCode = readShaderFromFile(fragmentPath);

    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    ID = glCreateProgram();

    unsigned int vertexID, fragmentID;
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    compileShader(vertexShaderCode, vertexID);
    compileShader(fragmentShaderCode, fragmentID);

    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      std::cout << "error shader program linking failed. log: " << infoLog << std::endl;
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
  }
  ~Shader() {
    glDeleteShader(ID);
  }

  void use() {
    glUseProgram(ID);
  }

  void setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }
  void setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }
  void setMat4(const std::string &name, glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
  }

};

#endif
