#pragma once

#include <algorithm>
#include <numeric>

namespace dtr {

template <typename CONTAINER>
typename CONTAINER::value_type median(CONTAINER& con){
  const typename CONTAINER::value_type M = con.size() / 2;
  std::nth_element(con.begin(), con.begin() + M, con.end());
  return con[M];
}

template <typename CONTAINER>
typename CONTAINER::value_type average(CONTAINER& con){
  return std::accumulate(con.begin(), con.end(), 0.0) / con.size();
}

} // namespace dtr
