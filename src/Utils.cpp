
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "Utils.h"
#include "Logger.h"
#include "TUI.h"
#include <cstdlib>
#include <iostream>
#include <limits>

#include <chrono>
#include <iostream>
#include <random>
#include <thread>

void Utils::clearTerm() {
  Logger::write("Clear Term Called", true);
  std::system("cls");

  TUI::printTitle();
}

void Utils::keyPress(WORD SCAN_CODE, const char *keyName) {
  INPUT key[2] = {};
  key[0].type = INPUT_KEYBOARD;
  key[0].ki.wScan = SCAN_CODE;
  key[0].ki.dwFlags = KEYEVENTF_SCANCODE;
  key[1].type = INPUT_KEYBOARD;
  key[1].ki.wScan = SCAN_CODE;
  key[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

  if (SendInput(2, key, sizeof(INPUT)) != 2) {
    std::cout << "SendInput " << keyName << " failed. Error: " << GetLastError()
              << '\n';
    return;
  }
  std::string cppKeyName = keyName;
  std::string msg = "keyPress called for key: [" + cppKeyName +
                    "] with SCAN_CODE: [" + std::to_string(SCAN_CODE) + "]\n";
  Logger::write(msg.c_str());
}

void Utils::releaseAllKeys() {
  // TODO:
}