#include <iostream>
#include <chrono>
#include <stdexcept>
#include <cmath> // fmax fmin
#include "eagerness.h"

double REGEN_DROP_RATE = 1.0; // per second 
double REGEN_BUMP_RATE = 2.0;
double DRAG_COEFFICIENT = 2.5;

Eagerness::Eagerness(double capacity):
currentEagerness(capacity),
maxEagerness(capacity),
resilience(0),
drag(0),
regeneration(0),
timeOfLatestExpenditure(std::chrono::system_clock::now())
{}

void Eagerness::print() {
  std::cout << "\nCurrent Eagerness: " << this->get_eagerness() << "\nMaximum Eagerness: " << this->maxEagerness << "\nResilience: " << this->resilience << "\nDrag: " << this->get_drag() << "\nRegeneration: " << this->get_regeneration() << std::endl;
}

int Eagerness::get_seconds_since_latest_expenditure() {
  return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - this->timeOfLatestExpenditure).count();
}

void Eagerness::expend(double expenditure) {
  // expending eagerness will cause a spike in regeneration, which tapers off over time
  // during this time, eagerness will regenerate
  
  if (expenditure > this->currentEagerness) {
    throw std::invalid_argument("expenditure is larger than available eagerness");
  }
  
  this->print();

  this->currentEagerness = this->get_eagerness() - 30.0;
  this->regeneration = this->get_regeneration() + REGEN_BUMP_RATE;

  this->timeOfLatestExpenditure = std::chrono::system_clock::now();

  this->print();

}

double Eagerness::get_regeneration(int secondsSinceLatestExpenditure) {
  return std::fmax(this->regeneration - (REGEN_DROP_RATE * secondsSinceLatestExpenditure), 0.0);
}

double Eagerness::get_regeneration() {
  int secondsSinceLatestExpenditure = this->get_seconds_since_latest_expenditure(); 
  return this->get_regeneration(secondsSinceLatestExpenditure); 
}

double Eagerness::get_drag(int secondsSinceExpenditure) {
  double missingEagerness = this->maxEagerness - this->currentEagerness; // would like to use get_eagerness, but that is a circular dependency...
  double drag = missingEagerness / this->maxEagerness;
  return drag * DRAG_COEFFICIENT;

}

double Eagerness::get_drag() {
  int secondsSinceLatestExpenditure = this->get_seconds_since_latest_expenditure(); 
  return this->get_drag(secondsSinceLatestExpenditure);
}

double Eagerness::get_eagerness() {
  return std::fmin(this->currentEagerness + this->get_change_in_eagerness_since_latest_expenditure(), this->maxEagerness);
}

double Eagerness::get_change_in_eagerness_at_time(int time) {
  return this->get_regeneration(time) / (1 + this->get_drag(time));
}

double Eagerness::get_change_in_eagerness_since_latest_expenditure() {
  //get time since expenditure, in seconds
  int secondsSinceLatestExpenditure = this->get_seconds_since_latest_expenditure(); 
  double sumEagernessRegenerated = 0.0;

  for (int i = 0; i <= secondsSinceLatestExpenditure; i++) {
    sumEagernessRegenerated += this->get_change_in_eagerness_at_time(i);
  }

  return sumEagernessRegenerated;
}

