#pragma once
#include <fstream>

extern const char *LOG_FILE_PATH;
extern bool SEND_VERBOSE;
extern bool LOG_FILE_ENABLED;

class Logger {
public:
  static const char *getFilePath();
  static void openFile();
  static void closeFile();
  static void write(const char *msg, bool verbose = false);

private:
  // static std::ofstream LOG_FILE;
};