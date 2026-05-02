#include "Logger.h"
#include "TUI.h"
#include <iostream>

int main() {
  TUI app;
  Logger::openFile();
  Logger::write("Program Started");
  app.run();
}