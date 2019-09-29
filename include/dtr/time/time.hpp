#pragma once

#include <chrono>

namespace dtr {

double now(){
  return std::chrono::duration_cast<
    std::chrono::duration<double, std::ratio<1>>>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

} // namespace dtr
