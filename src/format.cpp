#include <string>

#include <iostream>
#include "format.h"
using std::string;

string Format::timeFormat(long num) {
  string str = std::to_string(num);
  if (str.length() < 2) str.insert(0, 2 - str.length(), '0');
  return str;
}

string Format::ElapsedTime(long seconds) {
  long hours = 0, mins = 0, sec = 0;
  hours = seconds / 3600;
  mins = (seconds / 60) % 60;
  sec = seconds % 60;
  return timeFormat(hours) + ":" + timeFormat(mins) + ":" + timeFormat(sec);
}