#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
struct Time{
    public:
      Time(long secs) :time{secs}
    {
      hour = time / 3600;
      time = time % 3600;
      min = time / 60;
      time = time % 60;
      seconds = time;
   }
    long getHour () {return hour;}
    long getMin  () {return min;}
    long getSeconds () {return seconds;}
 
    private:
        long time;
        long hour;
        long min;
        long seconds;
       
    
};


string Format::ElapsedTime(long seconds) { 
  Time t = Time(seconds);
  
  std::stringstream ss;
  
  ss << std::setfill('0') << std::setw(2) << std::to_string(t.getHour()) << ":" << std::setfill('0') << std::setw(2) << std::to_string(t.getMin())
    << ":" << std::setfill('0') << std::setw(2) << std::to_string(t.getSeconds());
  
  return ss.str(); 
}