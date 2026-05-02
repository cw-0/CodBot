//
// Created by Caden on 4/29/2026.
//

#include "Script.h"

#include <random>

#include "Movement.h"
#include <iostream>
#include <thread>

std::random_device rd2;
std::mt19937 ranGen(rd2());

void Script::lookEyeLevel() {
  std::cout << "Looking Eye Level\n";
  Movement::rotate(0, -9000, 225, 0);
  Movement::rotate(0, 3800, 190, 0);
}

void Script::sprayAuto(int seconds) {
  std::cout << "Full Auto Spraying for " << seconds << " seconds\n";
  Movement::rightMouseHold();
  Movement::leftMouseHold(true);
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  Movement::leftMouseRelease();
  Movement::rightMouseRelease();
}

void Script::spraySemi(int shots) {
  std::cout << "Semi Auto Spraying for " << shots << " shots\n";
  Movement::rightMouseHold();
  for (int i = shots; i > 0; i--) {
    Movement::leftMouseClick();
    std::uniform_real_distribution<double> randDelay(0.023, .39);
    std::this_thread::sleep_for(
        std::chrono::duration<double>(randDelay(ranGen)));
  }
  Movement::rightMouseRelease();
}

void Script::dropShotSemi(int shots) {
  std::cout << "Dropshot Semi Auto for " << shots << " shots\n";
  Movement::prone();
  Script::spraySemi(shots);
} // end drop shot

void Script::dropShotAuto(int seconds) {
  std::cout << "Dropshot Full Auto for " << seconds << " seconds\n";
  Movement::prone();
  Script::sprayAuto(seconds);
} // end drop shot

void Script::runAndJump(int duration, bool slide) {
  // if (!slide) {
  //     std::cout << "Running and jumping for " << duration << "seconds\n";
  // } else {
  //     std::cout << "Running, jumping, and sliding for " << duration <<
  //     "seconds\n";
  // }
  Movement::move(duration, "forward", "none", 2, slide);
  Movement::jump();
}
