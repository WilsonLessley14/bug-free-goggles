#include "eagerness.h"
#include <chrono>
#include <thread>

int main() {
  using namespace std::this_thread; // sleep_for
  using namespace std::chrono; //system_clock, seconds
  Eagerness E(100);

  E.expend(15);
  
  sleep_for(seconds(3));

  E.print();

  return 0;
}

