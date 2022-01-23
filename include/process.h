#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <memory>

struct processStruct{
  int pid;
  std::string user;
  std::string command;
  float cpuUti;
  std::string ram;
  std::string upTime;
};

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  // rule of five
  Process(int pid) : data_{std::make_unique<processStruct>()}, pid_{pid} {}
  ~Process() = default;
  Process(const Process&);
  Process(Process&&);
  Process& operator=(const Process&);
  Process& operator=(Process&&);
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
  void calcProcessValues();
  std::unique_ptr<processStruct> data_;
 private:
  int pid_;
  
};

#endif