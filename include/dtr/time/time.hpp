#pragma once

#include <chrono>
#include <functional>
#include <iostream>


namespace dtr {

double now(){
  return std::chrono::duration_cast<
    std::chrono::duration<double, std::ratio<1>>>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

struct Benchmark_result {
  double min = -1.0;
  double max = -1.0;
  double median = -1.0;
  double average = -1.0;
};

template <std::size_t NUM_RUNS = 100>
Benchmark_result benchmark(std::function<void()> func){
  std::vector<double> timings;
  timings.reserve(NUM_RUNS);
  for (std::size_t i=0; i<NUM_RUNS; ++i){
    auto tic = now();
    func();
    auto toc = now();
    timings.push_back(toc - tic);
  }
  Benchmark_result ret;
  const auto [min, max] = std::minmax_element(timings.begin(), timings.end());
  ret.min = *min;
  ret.max = *max;
  ret.median = median(timings);
  ret.average = average(timings);
  return ret;
}

} // namespace dtr

std::ostream& operator<<(std::ostream& os, const dtr::Benchmark_result& res)
{
    os << "Min:" << res.min << " Max:" << res.max
       << " Median:" << res.median << " Average:" << res.average;
    return os;
}
