#include "vector_methods.h"
#include <iostream>
#include <stdexcept>

void printVector(const std::vector<int> vec) {
  for (int i : vec) {
    std::cout << ' ' << i;
  }
  std::cout << std::endl;
}

std::vector<int> addVectors(std::vector<int> left, std::vector<int> right) {
  if (left.size() != right.size()) {
    throw std::invalid_argument("input vectors are not the same size");
  }

  std::vector<int> sum;
  for (int i = 0; i < left.size(); i++) {
    sum.push_back(left[i] + right[i]);
  }
  return sum;
}

std::vector<int> scaleVector(int scalar, std::vector<int> vec) {
  std::vector<int> scaled;
  for (int i = 0; i < vec.size(); i++) {
    scaled.push_back(scalar * vec[i]);
  }
  return scaled;
}

