//
// Created by Caden on 4/29/2026.
//
#include "Movement.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <chrono>
#include <random>
#include <thread>
#include <iostream>

std::random_device rd;
std::mt19937 gen(rd());

WORD getScanCode(std::string_view direction) {
    if (direction == "forward") {
        return 0x11; // W key
    } else if (direction == "back") {
        return 0x1F; // S key
    } else if (direction == "right") {
        return 0x20; // D key
    } else if (direction == "left") {
        return 0x1E; // A key
    } else {
        return 0x11;
    }
}

void Movement::walk(int seconds, std::string const& direction, std::string const& direction2) {
    WORD SCAN_CODE = getScanCode(direction);
    WORD SCAN_CODE2{};
    INPUT keyDown{};
    keyDown.type = INPUT_KEYBOARD;
    keyDown.ki.wScan = SCAN_CODE;
    keyDown.ki.dwFlags = KEYEVENTF_SCANCODE;
    if (SendInput(1, &keyDown, sizeof(INPUT)) != 1) {
        std::cout << "SendInput keyDown failed. Error: " << GetLastError() << '\n';
        return;
    }

    if (direction2 != "none") {
        SCAN_CODE2 = getScanCode(direction2);
        INPUT keyDown2{};
        keyDown2.type = INPUT_KEYBOARD;
        keyDown2.ki.wScan = SCAN_CODE2;
        keyDown2.ki.dwFlags = KEYEVENTF_SCANCODE;

        std::uniform_real_distribution<double> randDelay(0.0, 2.0);
        std::this_thread::sleep_for(std::chrono::duration<double>(randDelay(gen)));
        if (SendInput(1, &keyDown2, sizeof(INPUT)) != 1) {
            std::cout << "SendInput keyDown2 failed. Error: " << GetLastError() << '\n';
            return;
        }

    }

    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    INPUT keyUp{};
    keyUp.type = INPUT_KEYBOARD;
    keyUp.ki.wScan = SCAN_CODE;
    keyUp.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    if (SendInput(1, &keyUp, sizeof(INPUT)) != 1) {
        std::cout << "SendInput keyUp failed. Error: " << GetLastError() << '\n';
        return;
    }
    if (direction2 != "none") {
        INPUT keyUp2{};
        keyUp2.type = INPUT_KEYBOARD;
        keyUp2.ki.wScan = SCAN_CODE2;
        keyUp2.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        if (SendInput(1, &keyUp2, sizeof(INPUT)) != 1) {
            std::cout << "SendInput keyUp failed. Error: " << GetLastError() << '\n';
            return;
        }

    }
} // END WALK

void Movement::rotate(int totalDx, int totalDy, int steps, int delayMs) {
    //////////////////////////////////////////////////////////
    ///     totalDx = Total Horizontal Movement
    ///     totalDY = Total Vertical Moement
    ///     steps = how many tiny movements (smoothness | more steps == slower)
    ///     delayMs = delay between each step (speed)
    ///////////////////////////////////////////////////////
    if (steps <= 0) {
        return;
    }

    int movedX{};
    int movedY{};

    for (int i = 1; i <= steps; ++i) {
        int targetX = totalDx * i / steps;
        int targetY = totalDy * i / steps;

        int stepDx = targetX - movedX;
        int stepDy = targetY - movedY;

        movedX = targetX;
        movedY = targetY;

        INPUT input{};
        input.type = INPUT_MOUSE;
        input.mi.dx = stepDx;
        input.mi.dy = stepDy;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;

        if (SendInput(1, &input, sizeof(INPUT)) != 1) {
            std::cout << "Mouse move failed. Error: " << GetLastError() << '\n';
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

void Movement::leftMouseClick() {
    INPUT mouseDown{};
    mouseDown.type = INPUT_MOUSE;
    mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    if (SendInput(1, &mouseDown, sizeof(INPUT)) != 1) {
        std::cout << "Left click failed. Error: " << GetLastError() << '\n';
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    INPUT mouseUp{};
    mouseUp.type = INPUT_MOUSE;
    mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    if (SendInput(1, &mouseUp, sizeof(INPUT)) != 1) {
        std::cout << "Left click failed. Error: " << GetLastError() << '\n';
    }
}

void Movement::leftMouseHold(bool recoilControl) {
    INPUT inputs{};

    inputs.type = INPUT_MOUSE;
    inputs.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;


    if (SendInput(1, &inputs, sizeof(INPUT)) != 1) {
        std::cout << "Left Mouse Hold failed. Error: " << GetLastError() << '\n';
    }

    if (recoilControl) {
        Movement::rotate(0, 500, 500, 1);
    }
}

void Movement::leftMouseRelease() {
    INPUT inputs{};

    inputs.type = INPUT_MOUSE;
    inputs.mi.dwFlags = MOUSEEVENTF_LEFTUP;


    if (SendInput(1, &inputs, sizeof(INPUT)) != 1) {
        std::cout << "Left Mouse Release failed. Error: " << GetLastError() << '\n';
    }
}

void Movement::rightMouseClick() {
    INPUT mouseDown{};
    mouseDown.type = INPUT_MOUSE;
    mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    if (SendInput(1, &mouseDown, sizeof(INPUT)) != 1) {
        std::cout << "Right click failed. Error: " << GetLastError() << '\n';
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    INPUT mouseUp{};
    mouseUp.type = INPUT_MOUSE;
    mouseUp.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    if (SendInput(1, &mouseUp, sizeof(INPUT)) != 1) {
        std::cout << "Right click failed. Error: " << GetLastError() << '\n';
    }
}

void Movement::rightMouseHold() {
    INPUT inputs{};

    inputs.type = INPUT_MOUSE;
    inputs.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;


    if (SendInput(1, &inputs, sizeof(INPUT)) != 1) {
        std::cout << "Right Mouse Hold failed. Error: " << GetLastError() << '\n';
    }
}

void Movement::rightMouseRelease() {
    INPUT inputs{};

    inputs.type = INPUT_MOUSE;
    inputs.mi.dwFlags = MOUSEEVENTF_RIGHTUP;


    if (SendInput(1, &inputs, sizeof(INPUT)) != 1) {
        std::cout << "Right Mouse Release failed. Error: " << GetLastError() << '\n';
    }
}
