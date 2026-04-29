//
// Created by Caden on 4/29/2026.
//

#pragma once
#include <string>

class Movement {
public:
    static void walk(int seconds, std::string const& direction="forward", std::string const& direction2="none");
    static void rotate(int totalDx, int totalDy, int steps, int delayMs);
    static void leftMouseClick();
    static void leftMouseHold(bool recoilControl=false);
    static void leftMouseRelease();
    static void rightMouseClick();
    static void rightMouseHold();
    static void rightMouseRelease();
};
