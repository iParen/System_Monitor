#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

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
  string os, ver, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> ver >> kernel;
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
  string variable;
  float MemTotal, MemFree, value;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> variable >> value) {
        if (variable == "MemTotal:") {
          MemTotal = value;
        }
        if (variable == "MemFree:") {
          MemFree = value;
          return (MemFree/MemTotal);
        }
      }
    }
  }
  return (MemFree/MemTotal);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long value;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
    return value;
  }
  return 0; 
  }

// TODO: Read and return the number of jiffies for the system Done in processor.cpp
//long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line, buffer;
  string spid = to_string(pid);
  int count = 14;
  long utime, stime, cutime, cstime;
  std::ifstream stream(kProcDirectory + spid + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(--count) {
      linestream >> buffer;
    }
    linestream >> utime >> stime >> cutime >> cstime;
  } 
  return utime+stime+cutime+cstime; 
  }


// TODO: Read and return the number of active jiffies for the system don in processor.cpp
//long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
//long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string variable;
  int value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> variable >> value) {
        if (variable == "processes") {
          return value;
        }
      }
    }
  }
  return value; 
  }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string variable, line;
  int value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> variable >> value) {
        if (variable == "procs_running")
        return value;
      }
    }
  }
  return value; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { 
  string spid = to_string(pid);
  string line, variable;
  float value;

  std::ifstream stream(kProcDirectory + spid + kStatusFilename);
  if(stream.is_open()) {
    while (std::getline (stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> variable >> value){
        if(variable == "VmSize:")
        return to_string(value/1000);
      }
    }
  }
  return to_string(value/1000); 
  }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string spid = to_string(pid);
  string variable, value, line;
  std::ifstream stream(kProcDirectory + spid + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> variable >> value) {
        if (variable == "Uid:")
        return value;
      }
    }
  }
  return 0; 
  }


// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line, op, x;
  int id;
  std::ifstream stream(LinuxParser::kPasswordPath);
  if (stream.is_open()) {
    while(std::getline(stream,line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);
    while(linestream >> op >> x >> id) {
     if (pid == id)
      return op;
      }
    }
  }
return 0; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }