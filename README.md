# System Monitor Application

This is a system/process monitor application written in C++ for linux operating systems. The starter code of this application is based on [this link](https://github.com/udacity/CppND-System-Monitor).  
## System Information
The following system informations are shown on the terminal:
- Linux release
- Kernel version
- CPU utilization
- Memory utilization
- Total running processes
- System up time
## Processes Information
The following data is shown for each process:  
- PID number of the process
- User of the process
- Cpu utilization for each process
- Memory utilization for each process
- Up time of the current process
- Command used to start the process
## Workflow
- clone the repository  
```  git clone  https://github.com/abdulkarim723/System-Monitor-Application.git  ```  
- install ncurses on your local system  
```sudo apt install libncurses5-dev libncursesw5-dev```