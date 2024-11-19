#include "lib/GLManager.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv) {

  GLManager manager = GLManager();
  manager.getVAO()[0] = 8;

  std::cout << manager.getVAO()[0] << std::endl;


  return 0;
}