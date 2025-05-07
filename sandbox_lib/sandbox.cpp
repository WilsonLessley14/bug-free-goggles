#include "eagerness.h"
#include <chrono>
#include <thread>
#include <cstdio>
#include <iostream>

int SPACEBAR_KEYCODE = 32;
int ESC_KEYCODE = 27;

void handleInput(bool inputBuffer[]) {
  int c;
  c = std::getchar();
  while(1) {
    inputBuffer[c] = true;
    c = std::getchar();
  }
}

using namespace std::this_thread; // sleep_for
using namespace std::chrono; //system_clock, seconds

int main() {
  Eagerness E(100);

  const int FPS = 60;
  
  const double SECONDS_PER_FRAME = 1.0 / FPS;

  auto previousTime = high_resolution_clock::now();

  bool inputBuffer[256] = {};
  
  std::system("stty raw opost");


  std::thread t(handleInput, inputBuffer);

  int counter = 0;
  while (true) {
    auto currentTime = high_resolution_clock::now();

    duration<double> elapsedTime = currentTime - previousTime;
    double deltaTime = elapsedTime.count();

    // process input
    if (inputBuffer[ESC_KEYCODE]) {
      return 0;
    }
    if (inputBuffer[SPACEBAR_KEYCODE]) {
      E.expend(10);
      std::cout << "expended 10 eagerness!" << std::endl;
      inputBuffer[SPACEBAR_KEYCODE] = false;
    }

    // update game state using deltaTime
    // render game
    
    double sleepTime = SECONDS_PER_FRAME - deltaTime;
    if (sleepTime > 0) {
      sleep_for(duration<double>(sleepTime));
    }

    counter++;
    if (counter >= 60) {
      std::cout << "one second has passed" << std::endl;
      E.print();
      counter = 0;
    }
    previousTime = high_resolution_clock::now();
  }

  std::system("stty cooked"); 

  return 0;
}

