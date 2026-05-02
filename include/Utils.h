#pragma once
#include <windows.h>

class Utils {
public:
  static void clearTerm();
  static void keyPress(WORD SCAN_CODE, const char *keyName);
  static void releaseAllKeys();
};
