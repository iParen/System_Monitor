#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int value = seconds;
    double hours = seconds/3600;
    int min = (seconds % 3600); // * 3600)/ 60;
    return string(to_string(value)+":"+to_string(hours)+":"+to_string(min)); }