#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"
#include <iostream>

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return  LinuxParser::Kernel();}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {return LinuxParser::MemoryUtilization();}

// DONE: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem();}

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { LinuxParser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { LinuxParser::TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime();}