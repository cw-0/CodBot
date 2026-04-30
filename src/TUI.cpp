//
// Created by Caden on 4/28/2026.
//

#include <chrono>
#include "State.h"
#include <thread>
#include <iostream>
#include <limits>
#include "Movement.h"
#include "Presets.h"
#include "Script.h"
#include "TUI.h"
#include "Utils.h"

std::string GREEN {"\033[32m"};
std::string YELLOW {"\033[33m"};
std::string RED {"\033[31m"};
std::string RESET {"\033[0m"};
std::string BOLD {"\033[1m"};

void TUI::run() {
    while (true){
        switch (int choice = menu()) {
            case 0:
                return;

            case 1:
                startBot(3);

            case 2:
                settingsMenu();
            default:
                continue;
        }

    } // END LOOP
} // END RUN

void TUI::printTitle() {
    // std::cout << "Black Ops 6 AFK Bot" << '\n';
    std::cout << R"(

  ____  _            _       ____
 |  _ \| |          | |     / __ \
 | |_) | | __ _  ___| | __ | |  | |_ __  ___
 |  _ <| |/ _` |/ __| |/ / | |  | | '_ \/ __|
 | |_) | | (_| | (__|   <  | |__| | |_) \__ \
 |____/|_|\__,_|\___|_|\_\  \____/| .__/|___/
                                  | |
    __             ______ _  __  _|_|        _
   / /       /\   |  ____| |/ / |  _ \      | |
  / /_      /  \  | |__  | ' /  | |_) | ___ | |_
 | '_ \    / /\ \ |  __| |  <   |  _ < / _ \| __|
 | (_) |  / ____ \| |    | . \  | |_) | (_) | |_
  \___/  /_/    \_\_|    |_|\_\ |____/ \___/ \__|


)";
    std::cout << "\t\t\t\t" << BOLD << "Keybinds:\n" << RESET;
    std::cout << YELLOW << "[ Left Alt ] - Pause Bot" << RESET << "|" << GREEN << " [ Right Alt ] - Resume Bot " << RESET << "|" << RED << " [ Right Ctrl ] - Exit\n" << RESET;
    std::cout << "\n\n";
}

int TUI::menu() {
    int choice;

    do {
        Utils::clearTerm();
        choice = -1;
        std::cout << "1. Start\n";
        std::cout << "2. Settings\n";
        std::cout << "0. Exit\n";

        std::cout << std::endl;
        std::cout << "> ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }
    } while (choice == -1);
    return choice;


}

void TUI::startBot(int waitTime) {
    //TODO: Add Choice Of Preset
    std::thread listener(State::changeState); // Listens for HotKeys
    std::thread inGameCheck(State::checkInGame); // Checks for Pixel
    for (int i = waitTime; i > 0; i--) {
        if (IS_PAUSED) { std::cout << "Pausing After Countdown.\n"; }
        std::cout << "Starting in " << i << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    State::checkState(); // Checks IN_GAME | PAUSED | SOFT_PAUSED and Pauses
    RUNNING_BOT = true;
    Utils::clearTerm();
    while (RUNNING_BOT){
        Presets::commonSoldier();
        Presets::crackhead();
    }
    State::endThreads();
}

void TUI::settingsMenu() {
    while (true) {
        Utils::clearTerm();

        int choice;

        std::cout << "0. Back\n";
        std::cout << "\n";
        std::cout << "> ";
        std::cin >> choice;

        if (choice == 0){
            return;
        }

    } // END LOOP
} // END settingsMenu


