#ifndef VECTOR_METHODS_H
#define VECTOR_METHODS_H

#include <iostream>

void printVector(const std::vector<int> vec);

/*
* func addVectors
*
* @param std::vector<int>left
* @param std::vector<int>right
*
* @return std::vector<int>
*
* @desc
* returns sum of provided vectors
*
* @throws
* std::invalid_argument if vectors are not same length
*
*/
std::vector<int> addVectors(std::vector<int> left, std::vector<int> right);

std::vector<int> scaleVector(int scalar, std::vector<int> vec);


#endif

