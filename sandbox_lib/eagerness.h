#ifndef EAGERNESS_H
#define EAGERNESS_H

#include <chrono>

class Eagerness {
  double currentEagerness, maxEagerness, resilience, drag, regeneration;
  std::chrono::time_point<std::chrono::system_clock> timeOfLatestExpenditure;

  double get_regeneration(int secondsSinceExpenditure);
  double get_regeneration();

  double get_drag(int secondsSinceExpenditure);
  double get_drag();

  double get_eagerness();
  double get_change_in_eagerness_at_time(int time);
  double get_change_in_eagerness_since_latest_expenditure();

  int get_seconds_since_latest_expenditure();


public:
  Eagerness(double capacity);
  void print();
  void expend(double expenditure);
  
};


#endif
