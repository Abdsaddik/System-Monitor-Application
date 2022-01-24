#include <curses.h>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "format.h"
#include "ncurses_display.h"
#include "system.h"
#include <thread>
#include <future>
#include <algorithm>
#include <memory>
#include <mutex>
#include <iostream>

using std::string;
using std::to_string;

std::mutex mutex_;

// 50 bars uniformly displayed from 0 - 100 %
// 2% is one bar(|)
std::string NCursesDisplay::ProgressBar(float percent) {
  std::string result{"0%"};
  int size{50};
  float bars{percent * size};

  for (int i{0}; i < size; ++i) {
    result += i <= bars ? '|' : ' ';
  }

  string display{to_string(percent * 100).substr(0, 4)};
  if (percent < 0.1 || percent == 1.0)
    display = " " + to_string(percent * 100).substr(0, 3);
  return result + " " + display + "/100%";
}

void NCursesDisplay::DisplaySystem(System& system, WINDOW* window) {
  auto processor_ = system.Cpu();
  std::future<float> ftr = std::async(&Processor::Utilization, processor_);
  int row{0};
  mvwprintw(window, ++row, 2, ("OS: " + system.OperatingSystem()).c_str());
  mvwprintw(window, ++row, 2, ("Kernel: " + system.Kernel()).c_str());
  mvwprintw(window, ++row, 2, "CPU: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  ftr.wait();
  wprintw(window, ProgressBar(ftr.get()).c_str());
  wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, ++row, 2, "Memory: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  wprintw(window, ProgressBar(system.MemoryUtilization()).c_str());
  wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, ++row, 2,
            ("Total Processes: " + to_string(system.TotalProcesses())).c_str());
  mvwprintw(
      window, ++row, 2,
      ("Running Processes: " + to_string(system.RunningProcesses())).c_str());
  mvwprintw(window, ++row, 2,
            ("Up Time: " + Format::ElapsedTime(system.UpTime())).c_str());
  wrefresh(window);
}

void NCursesDisplay::DisplayProcesses(std::vector<Process>&& processes,
                                      WINDOW* window, int& n) {
  int ret;
  int row{0};
  int const pid_column{2};
  int const user_column{9};
  int const cpu_column{20};
  int const ram_column{30};
  int const time_column{40};
  int const command_column{50};
  try
  {
    ret = wattron(window, COLOR_PAIR(2));
  if(ret!=OK){
    EndProg("Error by the function mvwprintw" );
  }
  ret = mvwprintw(window, ++row, pid_column, "PID");
  if(ret!=OK){
    EndProg("Error by the function mvwprintw" );
  }
  ret = mvwprintw(window, row, user_column, "USER");
  if(ret!=OK){
    EndProg("Error by the function mvwprintw" );
  }
  ret = mvwprintw(window, row, cpu_column, "CPU[%%]");
  if(ret!=OK){
    EndProg("Error by the function mvwprintw" );
  }
  ret = mvwprintw(window, row, ram_column, "RAM[MB]");
  if(ret!=OK){
    EndProg("Error by the function mvwprintw" );
  }
  ret = mvwprintw(window, row, time_column, "TIME+");
  if(ret!=OK){
    EndProg("Error by the function mvwprintw" );
  }
  ret = mvwprintw(window, row, command_column, "COMMAND");
  if(ret!=OK){
    EndProg("Error by the function mvwprintw" );
  }
  ret = wattroff(window, COLOR_PAIR(2));
  if(ret!=OK){
    EndProg("Error by init pair color" );
  }
  std::vector<std::future<void>> ftr;
  int processStartIndex = n-10;
  for (int i = processStartIndex; i < n; ++i) {
    ftr.emplace_back(std::async(LineDisplay, window, std::move(processes[i]), std::move(++row)));
  }
  std::for_each(ftr.begin(), ftr.end(), [](std::future<void>& f){f.wait();});
  }
  catch(const std::exception& e)
  {
    endwin();
    std::cerr << "Exception detected: " << e.what() << '\n';
  }
}

void NCursesDisplay::LineDisplay(WINDOW* win_, Process&& process_, int&& row_){
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  process_.calcProcessValues();
  std::lock_guard<std::mutex> lck(mutex_);
  // Clear the line
    mvwprintw(win_, row_, 2, (string(win_->_maxx - 2, ' ').c_str())); 
    auto &data = process_.data_;
    mvwprintw(win_, row_, 2, to_string(data->pid).c_str());
    mvwprintw(win_, row_, 9, data->user.c_str());
    mvwprintw(win_, row_, 20, to_string(data->cpuUti * 100).substr(0, 4).c_str());
    mvwprintw(win_, row_, 30, data->ram.c_str());
    mvwprintw(win_, row_, 40, data->upTime.c_str());
    mvwprintw(win_, row_, 50, data->command.substr(0, win_->_maxx - 46).c_str());
    wrefresh(win_);
}

void NCursesDisplay::Display(System& system, int n) {
  try
  {
  initscr();      // start ncurses
  noecho();       // do not print input values
  curs_set(0);    // turn the cursor off
  start_color();  // enable color
  int ch=0;
  int x_max{getmaxx(stdscr)};
  WINDOW* system_window = newwin(9, x_max - 1, 0, 0);
  if(system_window == NULL){
    EndProg("memory allocation error" );
  }
  WINDOW* process_window = newwin(3 + n, x_max - 1, system_window->_maxy + 1, 0);
  if(process_window == NULL){
    EndProg("memory allocation error" );
  }
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  halfdelay(5);
  while (1) { 
    ch = getch();
    if(ch == KEY_RIGHT) break;
    else if(ch == KEY_UP) { n++;}
    else if(ch == KEY_DOWN && n>10) {n--;}
    box(system_window, 0, 0);
    box(process_window, 0, 0);
    DisplaySystem(system, system_window);
    DisplayProcesses(std::move(system.Processes()), process_window, n);
    refresh();
    flushinp();
  }
  delwin(system_window);
  delwin(process_window);
  endwin();
  }
  catch(const std::exception& e)
  {
    endwin();
    std::cerr << "Exception detected: " <<  e.what() << '\n';
  }
}
void NCursesDisplay::EndProg(const char* msg){
  endwin();
  std::cout << msg << std::endl;
  exit(1);
}