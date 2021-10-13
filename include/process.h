#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_{pid} {}
  // return the pid of the process
  int Pid();
  // return the user of the current process
  std::string User();
  // return the command executed to run the process
  std::string Command();
  // return the used cpu utilization part of the current process
  float CpuUtilization() const;
  // return the RAM used by the current process
  std::string Ram();
  // return uptime of the current process
  long int UpTime();
  bool operator<(Process const& a) const;

 private:
  int pid_;
};

#endif