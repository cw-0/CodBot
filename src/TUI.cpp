//
// Created by Caden on 4/28/2026.
//

#include <chrono>
#include "State.h"
#include <thread>
#include <iostream>
#include <limits>
#include "Logger.h"
#include "Movement.h"
#include "Presets.h"
#include "Script.h"
#include <windows.h>
#include <shellapi.h>
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
                Logger::write("Exited Through Menu");
                return;

            case 1:
                Logger::write("Start Bot Selected In Menu");
                startBot(3);

            case 2:
                settingsMenu();
            case 3:
                ShellExecute(0, 0, "https://github.com/cw-0/CodBot#usage", 0, 0, SW_SHOW);
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
        std::cout << "3. Help (Opens GitHub Repo)\n";
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
    Logger::write("Hotkey Listener Thread Started");
    std::thread inGameCheck(State::checkInGame); // Checks for Pixel
    Logger::write("In Game Detection Thread Started");
    for (int i = waitTime; i > 0; i--) {
        if (IS_PAUSED) { std::cout << "Pausing After Countdown.\n"; }
        std::cout << "Starting in " << i << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    State::checkState(); // Checks IN_GAME | PAUSED | SOFT_PAUSED and Pauses
    RUNNING_BOT = true;
    RAN_ONCE = false;
    Utils::clearTerm();
    while (RUNNING_BOT){
        Presets::commonSoldier();
        Logger::write("Finished commonSoldier Preset");
        Presets::crackhead();
        Logger::write("Finished crackhead Preset");
    }
    State::endThreads();
    Logger::write("End Threads Called");
}

void TUI::settingsMenu() {
    Logger::write("Settings Menu Entered");
    while (true) {
        Utils::clearTerm();

        int choice;

        //TODO:
            std::cout << "1. Change Log File Destination\n";
            std::cout << "2. Toggle Log File Verbosity: " << (SEND_VERBOSE ? GREEN + "ON" : RED + "OFF") << RESET << "\n";
            std::cout << "3. Change Hot Keys\n";
        std::cout << "0. Back\n";
        std::cout << "\n";
        std::cout << "> ";
        std::cin >> choice;

        if (choice == 0){
            Logger::write("Exiting Settings Menu");
            return;
        } else {
            std::cout << "Coming Soon\n";
            std::cout << "Press Enter To Continue...";
            std::cin.ignore();
            char tmp = 'x';
            while (tmp != '\n') {
                std::cin.get(tmp);
            }
        }

    } // END LOOP
} // END settingsMenu


