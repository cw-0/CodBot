//
// Created by Caden on 4/29/2026.
//
#include "Movement.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include "Utils.h"

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
    return 0;
  }
}

void Movement::move(int seconds, std::string const &direction,
                    std::string const &direction2, int sprint, bool slide,
                    bool dive) {
  /////////////////////////////////////////
  /// seconds = How Long Movement Lasts
  /// sprint = 0 ~ Walk, 1 ~ Sprint, 2 ~ Tac Sprint
  /////////////////////////////////////////
  WORD d1SCAN_CODE = getScanCode(direction);
  WORD d2SCAN_CODE = getScanCode(direction2);
  WORD SHIFT_CODE = 0x2A; // Left Shift

  std::cout << "Moving " << direction
            << (d2SCAN_CODE ? "and " + direction2 : "") << " for " << seconds
            << " seconds";
  if (slide) {
    std::cout << " and sliding";
  }
  if (dive) {
    std::cout << " and diving";
  }
  std::cout << '\n';

  INPUT d1KeyUp{};
  d1KeyUp.type = INPUT_KEYBOARD;
  d1KeyUp.ki.wScan = d1SCAN_CODE;
  d1KeyUp.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

  INPUT d1KeyDown{};
  d1KeyDown.type = INPUT_KEYBOARD;
  d1KeyDown.ki.wScan = d1SCAN_CODE;
  d1KeyDown.ki.dwFlags = KEYEVENTF_SCANCODE;

  INPUT d2KeyUp{};
  d2KeyUp.type = INPUT_KEYBOARD;
  d2KeyUp.ki.wScan = d2SCAN_CODE;
  d2KeyUp.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

  INPUT d2KeyDown{};
  d2KeyDown.type = INPUT_KEYBOARD;
  d2KeyDown.ki.wScan = d2SCAN_CODE;
  d2KeyDown.ki.dwFlags = KEYEVENTF_SCANCODE;

  INPUT shiftUp{};
  shiftUp.type = INPUT_KEYBOARD;
  shiftUp.ki.wScan = SHIFT_CODE;
  shiftUp.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

  INPUT shiftDown{};
  shiftDown.type = INPUT_KEYBOARD;
  shiftDown.ki.wScan = SHIFT_CODE;
  shiftDown.ki.dwFlags = KEYEVENTF_SCANCODE;

  if (SendInput(1, &d1KeyDown, sizeof(INPUT)) != 1) {
    std::cout << "SendInput Direction 1 KeyDown failed. Error: "
              << GetLastError() << '\n';
    return;
  }

  if (d2SCAN_CODE) {
    std::uniform_real_distribution<double> randDelay(0.0, 2.0);
    std::this_thread::sleep_for(std::chrono::duration<double>(randDelay(gen)));
    if (SendInput(1, &d2KeyDown, sizeof(INPUT)) != 1) {
      std::cout << "SendInput Direction 2 KeyDown failed. Error: "
                << GetLastError() << '\n';
      return;
    }
  }

  // CLICK SPRINT
  if (sprint == 1 || sprint == 2) {
    if (SendInput(1, &shiftDown, sizeof(INPUT)) != 1) {
      std::cout << "SendInput shiftDown failed. Error: " << GetLastError()
                << '\n';
      return;
    }

    std::uniform_real_distribution<double> randDelay(0.2, 0.5);
    std::this_thread::sleep_for(std::chrono::duration<double>(randDelay(gen)));

    if (SendInput(1, &shiftUp, sizeof(INPUT)) != 1) {
      std::cout << "SendInput shiftUp failed. Error: " << GetLastError()
                << '\n';
      return;
    }
  }

  // HOLD TAC SPRINT
  if (sprint == 2) {
    // std::uniform_real_distribution<double> randDelay(0.0, 2.0);
    // std::this_thread::sleep_for(std::chrono::duration<double>(randDelay(gen)));
    if (SendInput(1, &shiftDown, sizeof(INPUT)) != 1) {
      std::cout << "SendInput shiftDown failed. Error: " << GetLastError()
                << '\n';
      return;
    }
  }

  if (slide || dive) {
    if (slide) {
      crouch();
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
    if (dive) {
      prone();
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    // re-enable tac sprint
    if (sprint == 2) {
      if (SendInput(1, &shiftUp, sizeof(INPUT)) != 1) {
        std::cout << "SendInput shiftUp failed. Error: " << GetLastError()
                  << '\n';
        return;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      if (SendInput(1, &shiftDown, sizeof(INPUT)) != 1) {
        std::cout << "SendInput shiftDown failed. Error: " << GetLastError()
                  << '\n';
        return;
      }
    }
  }

  // DELAY UNTIL KEYS RELEASED
  std::this_thread::sleep_for(std::chrono::seconds(seconds));

  // RELEASE TAC SPRINT
  if (sprint == 2) {
    if (SendInput(1, &shiftUp, sizeof(INPUT)) != 1) {
      std::cout << "SendInput shiftUp  failed. Error: " << GetLastError()
                << '\n';

      return;
    }
  }
  if (SendInput(1, &d1KeyUp, sizeof(INPUT)) != 1) {
    std::cout << "SendInput Direction 1 Key Up failed. Error: "
              << GetLastError() << '\n';
    return;
  }
  if (d2SCAN_CODE) {
    if (SendInput(1, &d2KeyUp, sizeof(INPUT)) != 1) {
      std::cout << "SendInput keyUp failed. Error: " << GetLastError() << '\n';
      return;
    }
  }
} // END MOVE

void Movement::jump() {
  std::cout << "Jumping\n";
  WORD SPACEBAR_CODE = 0x39;
  Utils::keyPress(SPACEBAR_CODE, "Space Bar");
}

void Movement::crouch() {
  std::cout << "Crouching\n";
  WORD Q_KEY = 0x10; // Q is my keybind for crouch
  Utils::keyPress(Q_KEY, "Q Key");
}

void Movement::prone() {
  std::cout << "Proning\n";
  WORD CTRL_CODE = 0x1D;
  Utils::keyPress(CTRL_CODE, "Left Control");
}

void Movement::grenade() {
  std::cout << "Throwing grenade\n";
  WORD O_KEY = 0x18;
  Utils::keyPress(O_KEY, "O Key");
}

void Movement::changeWeapon() {
  std::cout << "Changing Weapon\n";
  WORD ONE_KEY = 0x02; // Top Num Key 1
  Utils::keyPress(ONE_KEY, "num1 Key");
}

void Movement::skipKillcam() {
  WORD E_KEY = 0x12; // E key
  Utils::keyPress(E_KEY, "E Key");
}

void Movement::specialGadget() {
  std::cout << "Using Special Gadget\n";
  WORD X_KEY = 0x07; // X key
  Utils::keyPress(X_KEY, "X Key");
}

// --- MOUSE MOVEMENTS ---

void Movement::rotate(int totalDx, int totalDy, int steps, int delayMs) {
  //////////////////////////////////////////////////////////
  ///     totalDx = Total Horizontal Movement
  ///     totalDY = Total Vertical Moement
  ///     steps = how many tiny movements (smoothness | more steps == slower)
  ///     delayMs = delay between each step
  ///////////////////////////////////////////////////////
  std::cout << "Rotating: (" << totalDx << ", " << totalDy << ") in " << steps
            << " steps with " << delayMs << "ms delay\n";
  if (steps <= 0) {
    return;
  }

  int movedX{};
  int movedY{};

  for (int i = 1; i <= steps; ++i) {
    int targetX = totalDx * i / steps;
    int targetY = -1 * (totalDy * i / steps);

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
  INPUT mouseInputs[2] = {};
  mouseInputs[0].type = INPUT_MOUSE;
  mouseInputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

  mouseInputs[1].type = INPUT_MOUSE;
  mouseInputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

  if (SendInput(2, mouseInputs, sizeof(INPUT)) != 2) {
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
    Movement::rotate(0, -500, 50, 1);
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
  INPUT mouseInputs[2] = {};
  mouseInputs[0].type = INPUT_MOUSE;
  mouseInputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

  mouseInputs[1].type = INPUT_MOUSE;
  mouseInputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

  if (SendInput(2, mouseInputs, sizeof(INPUT)) != 2) {
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
    std::cout << "Right Mouse Release failed. Error: " << GetLastError()
              << '\n';
  }
}