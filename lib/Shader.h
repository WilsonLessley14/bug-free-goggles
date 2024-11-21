#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {

  //for debugging
  int success;
  char infoLog[512];

  const char* readShaderFromFile(const char* shaderPath) {
    std::string shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
      //open files
      shaderFile.open(shaderPath);

      std::stringstream vertexShaderStream;

      // read the file buffer contents into streams
      vertexShaderStream << shaderFile.rdbuf();

      shaderFile.close();

      shaderCode = vertexShaderStream.str();
    } catch(std::ifstream::failure e) {
      std::cout << "error reading shader from file" << std::endl;
    }
    return shaderCode.c_str();
  }

  unsigned int compileShader(const char* shaderCode) {
    unsigned int shaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderID, 1, &shaderCode, NULL);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success) {
      glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
      std::cout << "error shader compilation failed" << infoLog << std::endl;
    }

    glAttachShader(ID, shaderID);
    // so we can delete the shader after linking
    return shaderID;
  }

 public:

  // program id?
  unsigned int ID;

  // -- Method Signatures -- //

  // constructor reads and builds shader
  Shader(const char* vertexPath, const char* fragmentPath);
  // use/activate the shader
  void use();
  //utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

  // -- Method Definitions -- //
  Shader(const char* vertexPath, const char* fragmentPath) {
    const char* vertexShaderCode = readShaderFromFile(vertexPath);
    const char* fragmentShaderCode = readShaderFromFile(fragmentPath);

    ID = glCreateProgram();

    unsigned int vertexID = compileShader(vertexShaderCode);
    unsigned int fragmentID = compileShader(fragmentShaderCode);

    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      std::cout << "error shader program linking failed. log: " << infoLog << std::endl;
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
  }

  void use() {
    glUseProgram(ID);
  }

  void setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }
  void setInt(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void setFloat(const std::string &name, bool value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

};

#endif