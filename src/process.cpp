#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
// calculation method is taken from
// https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
float Process::CpuUtilization() {
  float cpuUti = 0;
  vector<string> statVal{};
  std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(pid_) +
                       "/stat");
  if (stream.is_open()) {
    string line;
    string val;
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int cnt = 0; cnt < 22; cnt++) {
      linestream >> val;
      statVal.push_back(val);
    }
    long sysFreq = sysconf(_SC_CLK_TCK);
    long upTimeSys = LinuxParser::UpTime();
    long upTimeProc = std::stol(statVal[13]);
    long sTimeKern = std::stol(statVal[14]);
    long cutime = std::stol(statVal[15]);
    long cstime = std::stol(statVal[16]);
    long startTime = std::stol(statVal[21]);
    long totalTime = upTimeProc + sTimeKern + cutime + cstime;
    float seconds = upTimeSys - (startTime / sysFreq);
    cpuUti = ((totalTime / sysFreq) / seconds) * 100;
  }
  return cpuUti;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return pid_ < a.pid_; }