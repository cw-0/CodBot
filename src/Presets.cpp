
#include "Presets.h"

#include <iostream>

#include "Movement.h"
#include "Script.h"
#include "State.h"

void Presets::commonSoldier() {
  std::cout << "Starting Common Soldier.\n";
  State::checkState();
  RAN_ONCE = true;

  Movement::move(1, "forward", "none", 2, true);
  State::checkState();

  Movement::rotate(-12000, -750, 200, 0);
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::lookEyeLevel();
  State::checkState();

  Movement::move(1, "forward", "none", 2, true);
  State::checkState();

  Movement::rotate(-8000, 200, 200, 0);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Script::lookEyeLevel();
  State::checkState();

  Movement::move(1, "forward", "none", 2, true, true);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::move(1, "forward", "none", 2, true);
  State::checkState();

  Movement::rotate(-16000, -150, 200, 0);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::dropShotAuto(3);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::move(3, "forward", "none", 2, true);
  State::checkState();

  Movement::rotate(24000, 50, 200, 0);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::rotate(-2000, -350, 200, 0);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::sprayAuto(1);
  State::checkState();

  Script::lookEyeLevel();
  State::checkState();

  Movement::rotate(300, 0, 200, 0);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::move(1, "forward", "right", 2, true);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::move(1, "forward", "left", 2, true);
  State::checkState();

  Movement::rotate(30000, 0, 200, 0);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::jump();
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Script::lookEyeLevel();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::grenade();
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::rotate(0, -8000, 225, 0);
  State::checkState();

  Script::lookEyeLevel();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::sprayAuto(3);
  State::checkState();

  Script::lookEyeLevel();
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::rotate(9000, 0, 200, 1);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Script::lookEyeLevel();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::rotate(-18000, 0, 100, 1);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::move(3, "forward", "none", 2, true);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::rotate(-6000, -250, 600, 0);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::changeWeapon();
  State::checkState();

  Script::lookEyeLevel();
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::dropShotSemi(12);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::changeWeapon();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::move(2, "forward", "none", 2, true, true);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::sprayAuto(1);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();
}

void Presets::crackhead() {
  std::cout << "CRACKHEAD RELEASED\n";

  Movement::move(1, "forward", "no", 2, true, true);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::rotate(50000, 0, 50, 1);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::move(1, "forward", "none", 2, true, true);
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::rotate(-50000, 0, 150, 1);
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::move(1, "forward", "none", 2, true, true);
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::jump();
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Movement::rotate(50000, 0, 200, 1);
  State::checkState();

  Script::spraySemi(3);
  State::checkState();

  Movement::skipKillcam();
  State::checkState();

  Script::dropShotAuto(3);
  State::checkState();

  Movement::specialGadget();
  State::checkState();

  Movement::skipKillcam();
  State::checkState();
}

void Presets::randomScripts() {
  // TODO: Add All Moves & Scripts to Array and randomly choose
  ;
}
