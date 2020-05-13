#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hours = 0;
    int min = 0;
    int sec = 0;
    hours = seconds/3600;
    min = (seconds % 3600) / 60; 
    sec = (seconds % 3600) % 60;
    return string(to_string(hours)+":"+to_string(min)+":"+to_string(sec)); }