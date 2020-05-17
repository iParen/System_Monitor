#include "ncurses_display.h"
#include "system.h"
#include <iostream>


#include "linux_parser.h"

int main() {

  //std::cout << LinuxParser::UpTime(1145) << "\n";
  System system;
  NCursesDisplay::Display(system);
}