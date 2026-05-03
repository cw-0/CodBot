#include "State.h"
#include "Logger.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <windows.h>

#include "Utils.h"

HDC dng = GetDC(NULL);
int CENTER_MINIMAP_X{152};
int CENTER_MINIMAP_Y{175};
int LOADOUT_DETECTION_X{1690};
int LOADOUT_DETECTION_Y{216};
int KICKED_DETECTION_X{693};
int KICKED_DETECTION_Y{479};
int KICKED_EXIT_BTN_X{615};
int KICKED_EXIT_BTN_Y{615};
int FIND_MATCH_BTN_X{243};
int FIND_MATCH_BTN_Y{924};
int QUICKPLAY_BTN_X{218};
int QUICKPLAY_BTN_Y{223};
int LOADOUT_POSX{228};
int LOADOUT_POSY{125};
bool IS_PAUSED{};
bool IS_SOFT_PAUSED{};
bool IN_GAME = false;
bool RUNNING_BOT = true;
// bool RAN_ONCE = false; // used to not auto click loadout until ran once
int MISSED_IN_GAME_CHECK = 0;
bool needThread = true;

void State::checkInGame() {
  needThread = true;
  while (needThread) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    COLORREF c = GetPixel(dng, CENTER_MINIMAP_X, CENTER_MINIMAP_Y);

    int R = (int)GetRValue(c);
    int G = (int)GetGValue(c);
    int B = (int)GetBValue(c);
    // std::cout << "RGB: (" << R << ", " << G << ", " << B << ")\n";

    // Detect if In Game
    if (R >= 140 && R <= 240) {
      if (G <= 30) {
        if (B >= 140 && B <= 240) {
          std::string msg = "In Game Pixel Found: (" + std::to_string(R) +
                            ", " + std::to_string(G) + ", " +
                            std::to_string(B) + ")";
          Logger::write(msg.c_str());
          IN_GAME = true;
          IS_SOFT_PAUSED = false;
          MISSED_IN_GAME_CHECK = 0;
          continue;
        }
      }
    }

    if (!IS_PAUSED) {
      // Detect Loadout
      c = GetPixel(dng, LOADOUT_DETECTION_X, LOADOUT_DETECTION_Y);
      R = static_cast<int>(GetRValue(c));
      G = static_cast<int>(GetGValue(c));
      B = static_cast<int>(GetBValue(c));
      // StrictDetect || LenientDetect
      if (R >= 105 && R <= 250) {                     // >= 200 || 105
        if (G >= 80 && G <= 195) {                    // >= 155 || 80
          if (B >= 30 && B <= 80) {                   // >= 50 || 30
            SetCursorPos(LOADOUT_POSX, LOADOUT_POSY); // Loadout1 Coord
            INPUT inputs[2] = {};
            inputs[0].type = INPUT_MOUSE;
            inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            inputs[1].type = INPUT_MOUSE;
            inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(2, inputs, sizeof(INPUT));
            std::string detectedMsg =
                "Loadout Screen Detected. RGB: (" + std::to_string(R) + ", " +
                std::to_string(G) + ", " + std::to_string(B) + ")";
            Logger::write(detectedMsg.c_str());
            std::string msg = "Clicked Loadout Position (" +
                              std::to_string(LOADOUT_POSX) + ", " +
                              std::to_string(LOADOUT_POSY) + ")";
            Logger::write(msg.c_str());
            continue;
          }
        }
      } // End of Detect Loadout

      std::this_thread::sleep_for(std::chrono::seconds(2));
      // Detect if Kicked
      c = GetPixel(dng, KICKED_DETECTION_X, KICKED_DETECTION_Y);
      R = static_cast<int>(GetRValue(c));
      G = static_cast<int>(GetGValue(c));
      B = static_cast<int>(GetBValue(c));
      if (R >= 210 && R <= 255) {
        if (G >= 60 && G <= 100) {
          if (B >= 0 && B <= 20) {
            std::cout << "Kicked Screen Detected\nStarting New Game...\n";
            std::string kickedMsg =
                "Kicked Screen Detected. RGB: (" + std::to_string(R) + ", " +
                std::to_string(G) + ", " + std::to_string(B) + ")";
            Logger::write(kickedMsg.c_str());
            INPUT inputs[2] = {};
            inputs[0].type = INPUT_MOUSE;
            inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            inputs[1].type = INPUT_MOUSE;
            inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

            std::string exitClickedMsg =
                "Clicked Exit Button: (" + std::to_string(KICKED_EXIT_BTN_X) +
                ", " + std::to_string(KICKED_EXIT_BTN_Y) + ")";
            Logger::write(exitClickedMsg.c_str());
            SetCursorPos(KICKED_EXIT_BTN_X, KICKED_EXIT_BTN_Y);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            SendInput(2, inputs, sizeof(INPUT));
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::string findMatchClickedMsg =
                "Clicked Find Match Button: (" +
                std::to_string(FIND_MATCH_BTN_X) + ", " +
                std::to_string(FIND_MATCH_BTN_Y) + ")";
            Logger::write(findMatchClickedMsg.c_str());
            SetCursorPos(FIND_MATCH_BTN_X, FIND_MATCH_BTN_Y);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            SendInput(2, inputs, sizeof(INPUT));
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::string quickplayClickedMsg =
                "Clicked Quickplay Button: (" +
                std::to_string(QUICKPLAY_BTN_X) + ", " +
                std::to_string(QUICKPLAY_BTN_Y) + ")";
            Logger::write(quickplayClickedMsg.c_str());
            SetCursorPos(QUICKPLAY_BTN_X, QUICKPLAY_BTN_Y);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            SendInput(2, inputs, sizeof(INPUT));
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
          }
        }
      } // End Kick Detection
    } // End If Not Paused

    // Not In Game
    std::string msg = "In Game Pixel NOT Found: (" + std::to_string(R) + ", " +
                      std::to_string(G) + ", " + std::to_string(B) + ")";
    Logger::write(msg.c_str());
    MISSED_IN_GAME_CHECK++;
    std::string missCheckMsg = "Missed In Game Checks In a Row Count: " +
                               std::to_string(MISSED_IN_GAME_CHECK);
    Logger::write(missCheckMsg.c_str());
    if (MISSED_IN_GAME_CHECK >= 3) {
      IN_GAME = false;
      IS_SOFT_PAUSED = true;
    }
  } // End of while needThread

  std::cout << "In Game Check Thread Terminated\n";
  Logger::write("In Game Check Thread Terminated");
}

void State::checkState() {
  Logger::write("Check State Called", true);
  if (!IN_GAME) {
    IS_SOFT_PAUSED = true;
  }
  if (IS_PAUSED || IS_SOFT_PAUSED) {
    Utils::clearTerm();
    std::cout << (IS_PAUSED
                      ? "Manually Paused\n"
                      : "Waiting For Loadout Screen or In Game Detection\n");
    Logger::write((IS_PAUSED
                       ? "Manually Paused\n"
                       : "Waiting For Loadout Screen or In Game Detection\n"));
    while (IS_PAUSED || IS_SOFT_PAUSED) {
      // CLICK ON LOADOUT POS
      // if (!IS_PAUSED) {
      //   // ONLY CLICK ON LOADOUT POS IF IT HAS BEEN IN GAME ONCE ALREADY
      //   // if (!RAN_ONCE) {
      //   //
      //   //   continue;
      //   // }
      //
      //   std::this_thread::sleep_for(std::chrono::seconds(3));
      //   SetCursorPos(LOADOUT_POSX, LOADOUT_POSY); // Loadout1 Coord
      //   INPUT inputs[2] = {};
      //   inputs[0].type = INPUT_MOUSE;
      //   inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
      //   inputs[1].type = INPUT_MOUSE;
      //   inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
      //   SendInput(2, inputs, sizeof(INPUT));
      //
      //   if (SEND_VERBOSE) { // no need to create msg if not sending
      //     std::string msg = "Clicked Loadout Position (" +
      //                       std::to_string(LOADOUT_POSX) + ", " +
      //                       std::to_string(LOADOUT_POSY) + ")";
      //     Logger::write(msg.c_str(), true);
      //   }
      // };
    }
    Utils::clearTerm();
    std::cout << "Resumed.\n";
    return;
  } // END IF IS PAUSED

} // END CHECK STATE

void State::changeState() {
  needThread = true;
  while (needThread) {
    if (GetKeyState(0xA4) & 0x8000 && !IS_PAUSED) { // Left Alt
      IS_PAUSED = true;
      Logger::write("Paused : Hot Key Pressed");
      std::cout << "PAUSING\n";
    }

    if (GetKeyState(0xA5) & 0x8000 && IS_PAUSED) { // Right Alt
      IS_PAUSED = false;
      Logger::write("Resuming : Hot Key Pressed");
      std::cout << "RESUMING\n";
    }

    if (GetKeyState(0xA3) & 0x8000) { // Right Ctrl Stop Bot
      Utils::clearTerm();
      std::cout << "Exiting\n";
      Logger::write("Exiting : Hot Key Pressed");
      exit(0);
    }
  }
  std::cout << "Listener Thread Terminated\n";
  Logger::write("Hot Key Thread Terminated");
}

void State::endThreads() {
  needThread = false;
  Logger::write("All Threads Ended");
}