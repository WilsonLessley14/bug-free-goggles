#ifndef EAGERNESS_H
#define EAGERNESS_H

#include <chrono>

class Eagerness {
  int currentEagerness, maxEagerness, resilience, drag, regeneration;
  std::chrono::time_point<std::chrono::system_clock> timeOfLatestExpenditure;

  int get_regeneration(int secondsSinceExpenditure);
  int get_regeneration();
  int get_eagerness();

public:
  Eagerness(int capacity);
  void print();
  void expend(int expenditure);
  
};


#endif
