//
// Created by Caden on 4/29/2026.
//
#pragma once

class Script {
public:
  static void lookEyeLevel();
  static void sprayAuto(int seconds);
  static void spraySemi(int shots);
  static void dropShotSemi(int shots);
  static void dropShotAuto(int seconds);
  static void runAndJump(int duration, bool slide);
};