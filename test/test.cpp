#include "dtr/math/math.hpp"
#include "dtr/time/time.hpp"

#include <iostream>
#include <vector>

void some_function(){
  volatile int sum = 0;
  for (int i=0; i<1e6; ++i){
    sum += i;
  }
}

int main(){
  std::vector<double> vec{ 5, 6, 4, 3, 2, 6, 7, 9, 3, 1.5 };
  auto median = dtr::median(vec);
  std::cout << "The median is: " << median << std::endl;
  auto average = dtr::average(vec);
  std::cout << "The average is: " << average << std::endl;
  auto now = dtr::now();
  std::cout << "Time since epoch is: " << now << std::endl;
  auto res = dtr::benchmark(some_function);
  std::cout << "Benchmark result is: " << res << std::endl;
}
