#include <unistd.h>
#include <iostream>
#include <sstream>
#include "format.h"
#include "linux_parser.h"
#include "ncurses_display.h"
#include "system.h"
using std::istringstream;
using std::string;
using std::vector;
using std::endl;
using std::cout;

// std::ostream& operator<<(std::ostream& out, const vector<string>& vec) {
//   for (auto it : vec) out << it << " ";
//   out << endl;
//   return out;
// }
// float MemoryUtilization() {
//   long memTotal = LinuxParser::GetSystemValue("MemTotal:",
//   LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
//   long memFree = LinuxParser::GetSystemValue("MemFree:",
//   LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
//   return static_cast<float>(memTotal) - static_cast<float>(memFree);
// }

// int RunningProcesses() {
//   return LinuxParser::GetSystemValue("procs_running",
//   LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
// }

// int TotalProcesses() {
//   return LinuxParser::GetSystemValue("processes", LinuxParser::kProcDirectory
//   + LinuxParser::kStatFilename);
// }

// string Command(int pid) {
//   string cmd;
//   std::fstream stream(LinuxParser::kProcDirectory + std::to_string(pid) +
//   "/cmdline");
//   if(stream.is_open()) std::getline(stream, cmd);
//   return cmd;
// }

// string Ram(int pid) {
//   long siztInKiB = LinuxParser::GetSystemValue("VmSize:",
//   LinuxParser::kProcDirectory + std::to_string(pid) + "/status");
//   std::ostringstream outStr;
//   outStr << static_cast<double>(siztInKiB)/1024;
//   return outStr.str();
// }

// string Uid(int pid) {
//   long uid = LinuxParser::GetSystemValue("Uid:", LinuxParser::kProcDirectory
//   + std::to_string(pid) + "/status");
//   return std::to_string(uid);
// }

// long UpTime(int pid) {
//   string line, val;
//   std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(pid) +
//   "/stat");
//   if(stream.is_open()){
//     std::getline(stream, line);
//     std::istringstream linestream(line);
//     for(auto cnt=0; cnt<22;cnt++){
//       linestream >> val;
//       if(cnt==21){
//         std::cout << "val = " << std::stoi(val) << " , " <<
//         Format::ElapsedTime(std::stoi(val));
//         return std::stoi(val);
//       }
//     }
//   }
//   return 0;
// }

// float CpuUtilization() {
//   long active = LinuxParser::ActiveJiffies();
//   long idle = LinuxParser::IdleJiffies();
//   usleep(1000000);
//   long activeNew = LinuxParser::ActiveJiffies();
//   long idleNew = LinuxParser::IdleJiffies();

//   long total = active + idle;
//   long totalNew = activeNew + idleNew;

//   long totald = totalNew - total;
//   long idled = idleNew - idle;
//   return static_cast<float>((totald - idled))/totald;
// }

// string ElapsedTime(long seconds) {
//     long hours = 0, mins = 0, sec = 0;
//     string minStr, secStr;
//     hours = seconds / 3600;
//     mins = (seconds - hours*3600)/60;
//     minStr = mins<10 ?  "0" + std::to_string(mins) : std::to_string(mins);
//     sec = seconds - hours*3600 - mins*60;
//     secStr = sec<10 ? "0" + std::to_string(sec) : std::to_string(sec);
//     string timeFormatted = std::to_string(hours) + ":" + minStr + ":" +
//     secStr;
//     return timeFormatted;
// }

// float CpuUtilization() {
//     float cpuUti = 0;
//     vector<string> statVal {};
//     std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(1) +
//     "/stat");
//     if(stream.is_open()){
//         string line; string val;
//         std::getline(stream, line);
//         std::istringstream linestream(line);
//         for(int cnt=0; cnt<22; cnt++){
//             linestream >> val;
//             statVal.push_back(val);
//         }
//         long sysFreq = sysconf(_SC_CLK_TCK);
//         long upTimeSys = LinuxParser::UpTime();
//         long upTimeProc = std::stol(statVal[13]);
//         long sTimeKern = std::stol(statVal[14]);
//         long cutime = std::stol(statVal[15]);
//         long cstime = std::stol(statVal[16]);
//         long startTime = std::stol(statVal[21]);
//         long totalTime = upTimeProc + sTimeKern + cutime + cstime;
//         float seconds = upTimeSys - (startTime/sysFreq);
//         cpuUti = ((totalTime/sysFreq)/seconds) * 100;
//     }
//     return cpuUti;
// }

int main() {
  System system;
  NCursesDisplay::Display(system);
  // std::cout << MemoryUtilization() << endl;
  // std::cout << RunningProcesses() << endl;
  // std::cout << TotalProcesses() << endl;
  // std:: cout << Command(1555) << endl;
  // std:: cout << Ram(1090) << endl;
  // auto pids = LinuxParser::Pids();
  // for (auto it: pids)
  // std:: cout << Uid(it) << endl;
  // std:: cout << UpTime(1599) << endl;
  // std:: cout << CpuUtilization() << endl;
  // std::cout << ElapsedTime(3700) << endl;
  // std::cout << "exit correctly\n";
  // cout << CpuUtilization() << endl;
}