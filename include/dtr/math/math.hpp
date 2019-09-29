#pragma once

#include <algorithm>
#include <numeric>

namespace dtr {

template <typename CONTAINER>
typename CONTAINER::value_type median(CONTAINER& con){
  std::nth_element(con.begin(), con.begin() + con.size()/2, con.end());
  return con[con.size()/2];
}

template <typename CONTAINER>
typename CONTAINER::value_type average(CONTAINER& con){
  return std::accumulate(con.begin(), con.end(), 0.0) / con.size();
}

} // namespace dtr
