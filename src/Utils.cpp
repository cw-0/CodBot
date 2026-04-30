
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <cstdlib>
#include <iostream>
#include <limits>
#include "TUI.h"
#include "Utils.h"


#include <chrono>
#include <random>
#include <thread>
#include <iostream>

void Utils::clearTerm() {
    std::system("cls");
    TUI::printTitle();
}

void Utils::keyPress(WORD SCAN_CODE, const char* keyName) {
    INPUT key[2] = {};
    key[0].type = INPUT_KEYBOARD;
    key[0].ki.wScan = SCAN_CODE;
    key[0].ki.dwFlags = KEYEVENTF_SCANCODE;
    key[1].type = INPUT_KEYBOARD;
    key[1].ki.wScan = SCAN_CODE;
    key[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    if (SendInput(2, key, sizeof(INPUT)) != 2) {
        std::cout << "SendInput " << keyName << " failed. Error: " << GetLastError() << '\n';
        return;
    }
}

void Utils::releaseAllKeys() {
 // TODO:
}