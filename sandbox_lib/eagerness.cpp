#include <iostream>
#include <chrono>
#include <stdexcept>
#include "eagerness.h"

int REGEN_DROP_RATE = 1; // per second 

Eagerness::Eagerness(int capacity):
currentEagerness(capacity),
maxEagerness(capacity),
resilience(0),
drag(0),
regeneration(0),
timeOfLatestExpenditure(std::chrono::system_clock::now())
{}

void Eagerness::print() {
  std::cout << "\nCurrent Eagerness: " << this->get_eagerness() << "\nMaximum Eagerness: " << this->maxEagerness << "\nResilience: " << this->resilience << "\nDrag: " << this-> drag << "\nRegeneration: " << this->get_regeneration() << std::endl;
}

void Eagerness::expend(int expenditure) {
  // expending eagerness will cause a spike in regeneration, which tapers off over time
  // during this time, eagerness will regenerate
  
  if (expenditure > this->currentEagerness) {
    throw std::invalid_argument("expenditure is larger than available eagerness");
  }
  
  this->print();

  this->currentEagerness -= expenditure;
  this->regeneration += 5;

  this->timeOfLatestExpenditure = std::chrono::system_clock::now();

  this->print();

}

int Eagerness::get_regeneration(int secondsSinceExpenditure) {
  return this->regeneration - (REGEN_DROP_RATE * secondsSinceExpenditure);
}

int Eagerness::get_regeneration() {
  int secondsSinceLatestExpenditure = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - this->timeOfLatestExpenditure).count();
  return this->regeneration - (REGEN_DROP_RATE * secondsSinceLatestExpenditure);
}

int Eagerness::get_eagerness() {
  //get time since expenditure, in seconds
  int secondsSinceLatestExpenditure = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - this->timeOfLatestExpenditure).count();
  int sumEagernessRegenerated = 0;

  for (int i = 0; i <= secondsSinceLatestExpenditure; i++) {
    sumEagernessRegenerated += get_regeneration(i);
  }
  return this->currentEagerness + sumEagernessRegenerated;
}

