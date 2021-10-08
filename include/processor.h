#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();

 private:
  // save the value of cpu utilization for a futue use
  float utiVal;
};

#endif