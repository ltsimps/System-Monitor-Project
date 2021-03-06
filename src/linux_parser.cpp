#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include <sstream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  string line,key, value;
  float utilization = 0.0;
  float memTotal, memFree, memAvailable;
  
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), 'k', ' ');
      std::replace(line.begin(), line.end(), 'B', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          //std::replace(value.begin(), value.end(), '_', ' ');
          //return value;
          std::stringstream s(value);
          s >> memTotal;
         //probaly super buggy if keys are out of order, use regex is probably more roboust         
        } else if(key == "MemFree") {
           std::stringstream s(value);
           s >> memFree;
           return (memFree-memTotal)/memTotal;

        }
      }
    }
  }
  return utilization; //default return;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptimeTotal, idleUptime = 0;
  string line,key, value;

  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> uptimeTotal >> idleUptime;
      
    }


  }
  return uptimeTotal; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  
  
  
  
  
  
  }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 

 std::ifstream filestream(kProcDirectory + kStatFilename);
  string line,key, value;
  float processes = 0.0;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          //std::replace(value.begin(), value.end(), '_', ' ');
          //return value;
          std::stringstream s(value);
          s >> processes;
         //probaly super buggy if keys are out of order, use regex is probably more roboust         
        } else {
          continue;

        }
      }
    }
  }
  return processes; 
 

}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 

  std::ifstream filestream(kProcDirectory + kStatFilename);
  string line,key, value;
  float runningProcs = 0.0;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          //std::replace(value.begin(), value.end(), '_', ' ');
          //return value;
          std::stringstream s(value);
          s >> runningProcs;
         //probaly super buggy if keys are out of order, use regex is probably more roboust         
        } else {
          continue;

        }
      }
    }
  }
  return runningProcs;
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }