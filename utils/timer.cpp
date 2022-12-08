#include "timer.h"

#include <chrono>

double gettime() {
  using clock = std::chrono::steady_clock;
  using dns = std::chrono::duration<double, std::nano>;
  using tpns = std::chrono::time_point<clock, dns>;
  static tpns basetime = clock::now();
  tpns curtime = clock::now();
  return (double)((curtime - basetime).count()) / 1e9;
}
