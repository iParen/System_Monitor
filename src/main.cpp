#include "ncurses_display.h"
#include "system.h"
#include <iostream>

#include "linux_parser.h" // jft
#include <vector>

int main() {
  std::vector<int> vTest;
  LinuxParser::Pids() = vTest;
  std::cout << vTest[0] << "\n"; // Jft
  //System system;
  //NCursesDisplay::Display(system);
}