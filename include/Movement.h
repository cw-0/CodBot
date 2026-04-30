//
// Created by Caden on 4/29/2026.
//

#pragma once
#include <string>

class Movement {
public:
    static void move(int seconds, std::string const& direction="forward", std::string const& direction2="none", int sprint=0, bool slide=false, bool dive=false);
    static void jump();
    static void crouch();
    static void prone();
    static void changeWeapon();
    static void grenade();
    static void skipKillcam();
    static void specialGadget();
    static void rotate(int totalDx, int totalDy, int steps, int delayMs);
    static void leftMouseClick();
    static void leftMouseHold(bool recoilControl=false);
    static void leftMouseRelease();
    static void rightMouseClick();
    static void rightMouseHold();
    static void rightMouseRelease();
};
