#pragma once

#include <chrono>
#include <functional>
#include <iostream>

namespace dtr {

double now() {
  return std::chrono::duration_cast<
             std::chrono::duration<double, std::ratio<1>>>(
             std::chrono::high_resolution_clock::now().time_since_epoch())
      .count();
}

struct Benchmark_result {
  double min = -1.0;
  double max = -1.0;
  double median = -1.0;
  double average = -1.0;
};

template <typename RET, typename... ARGS>
Benchmark_result benchmark(std::size_t num_runs,
                           std::function<RET(ARGS...)> func, ARGS&&... args) {
  std::vector<double> timings;
  timings.reserve(num_runs);
  for (std::size_t i = 0; i < num_runs; ++i) {
    auto tic = now();
    func(std::forward<ARGS>(args)...);
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

template <typename RET, typename... ARGS>
Benchmark_result benchmark(std::size_t num_runs, RET (*func)(ARGS...),
                           ARGS&&... args) {
  std::function<RET(ARGS...)> wrapper = func;
  return benchmark(num_runs, wrapper, std::forward<ARGS>(args)...);
}

} // namespace dtr

std::ostream &operator<<(std::ostream &os, const dtr::Benchmark_result &res) {
  os << "Min:" << res.min << " Max:" << res.max << " Median:" << res.median
     << " Average:" << res.average;
  return os;
}
