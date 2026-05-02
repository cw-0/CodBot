//
// Created by Caden on 4/28/2026.
//
#pragma once

class TUI {
public:
  void run();
  static void printTitle();

private:
  static int menu();
  static void settingsMenu();
  static void startBot(int waitTime);
};
