#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    long hours = 0, mins = 0, sec = 0;
    hours = seconds / 3600;
    mins = (seconds - hours*3600)/60;
    sec = seconds - hours*3600 - mins*60;
    string timeFormatted = std::to_string(hours) + ":" + std::to_string(mins) + ":" + std::to_string(sec);
    return timeFormatted;
}