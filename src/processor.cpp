#include<iostream>
#include<string>
#include <fstream>
#include <numeric>
#include <unistd.h>
#include <vector>

#include "processor.h"
#include "linux_parser.h"

using std::string;
 
std::vector<size_t> get_cpu_times() {
    std::vector<size_t> times;
    std::ifstream stream(LinuxParser::kProcDirectory +  LinuxParser::kStatFilename);
    if (stream.is_open()) {
        stream.ignore(5, ' '); // Skip the 'cpu' prefix.
        for (size_t time; stream >> time; times.push_back(time));
        return times;
    }
    return times;
}
 
bool get_cpu_times(size_t &idle_time, size_t &total_time) {
    const std::vector<size_t> cpu_times = get_cpu_times();
    if (cpu_times.size() < 4)
        return false;
    idle_time = cpu_times[3];
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
    return true;
}


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    size_t previous_idle_time, previous_total_time;
    size_t idle_time, total_time; 
    get_cpu_times(previous_idle_time, previous_total_time); 
    sleep(1);
    get_cpu_times(idle_time, total_time);
    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;
    const float utilization = (1.0 - idle_time_delta / total_time_delta);
       
    return utilization; 
    }


 