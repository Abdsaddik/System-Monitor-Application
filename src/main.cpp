#include <iostream>
#include <sstream>
#include "linux_parser.h"
#include "ncurses_display.h"
#include "system.h"
#include <unistd.h>
#include "format.h"
using std::istringstream;
using std::string;
using std::vector;
using std::endl;

std::ostream& operator<<(std::ostream& out, const vector<string>& vec) {
  for (auto it : vec) out << it << " ";
  out << endl;
  return out;
}
float MemoryUtilization() {
  long memTotal = LinuxParser::GetSystemValue("MemTotal:", LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  long memFree = LinuxParser::GetSystemValue("MemFree:", LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  return static_cast<float>(memTotal) - static_cast<float>(memFree);
}

int RunningProcesses() {
  return LinuxParser::GetSystemValue("procs_running", LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
}

int TotalProcesses() {
  return LinuxParser::GetSystemValue("processes", LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
}

string Command(int pid) {
  string cmd;
  std::fstream stream(LinuxParser::kProcDirectory + std::to_string(pid) + "/cmdline");
  if(stream.is_open()) std::getline(stream, cmd); 
  return cmd;
}

string Ram(int pid) {
  long siztInKiB = LinuxParser::GetSystemValue("VmSize:", LinuxParser::kProcDirectory + std::to_string(pid) + "/status");
  std::ostringstream outStr;
  outStr << static_cast<double>(siztInKiB)/1024;
  return outStr.str();
}

string Uid(int pid) {
  long uid = LinuxParser::GetSystemValue("Uid:", LinuxParser::kProcDirectory + std::to_string(pid) + "/status");
  return std::to_string(uid);
}

long UpTime(int pid) {
  long uptime = 0;
  string line, val;
  std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(pid) + "/stat");
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(auto cnt=0; cnt<22;cnt++){
      linestream >> val;
      if(cnt==21){
        std::cout << "val = " << std::stoi(val) << " , " <<  Format::ElapsedTime(std::stoi(val));
        return std::stoi(val);
      }
    }
  }
  return 0;
}

int main() {
  // System system;
  // NCursesDisplay::Display(system);
  std::cout << MemoryUtilization() << endl;
  std::cout << RunningProcesses() << endl;
  std::cout << TotalProcesses() << endl;
  std:: cout << Command(1555) << endl;
  std:: cout << Ram(1090) << endl;
  auto pids = LinuxParser::Pids();
  for (auto it: pids)
  std:: cout << Uid(it) << endl;
  std:: cout << UpTime(1599) << endl;
}