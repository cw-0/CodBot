#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iostream>

bool SEND_VERBOSE = true; // Get this value from .INI ~ add a toggle
bool LOG_FILE_ENABLED = true;

const char *LOG_FILE_PATH = Logger::getFilePath();
std::ofstream LOG_FILE;

const char *Logger::getFilePath() {
  // Add Parsing .ini for FILE_PATH ~ Allow User to select file path with
  // Windows File Dialog
  return "Log.txt";
}

void Logger::openFile() {
  LOG_FILE.open(LOG_FILE_PATH, std::ios::app);
  if (!LOG_FILE.is_open()) {
    std::cout << "Failed to open Log File: " << LOG_FILE_PATH << '\n';
  }
}

void Logger::closeFile() { LOG_FILE.close(); }

void Logger::write(const char *msg, bool verbose) {
  if (verbose && !SEND_VERBOSE) {
    return;
  }
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  LOG_FILE << std::ctime(&now_c)
           << " | Verbose: " << (SEND_VERBOSE ? "on" : "off") << '\n'
           << " | " << msg << "\n\n";
}
