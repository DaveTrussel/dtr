#include "dtr/math/math.hpp"
#include "dtr/time/time.hpp"

#include <iostream>
#include <vector>


int main(){
  std::vector<double> vec{ 5, 6, 4, 3, 2, 6, 7, 9, 3, 1.5 };
  auto median = dtr::median(vec);
  std::cout << "The median is: " << median << std::endl;
  auto average = dtr::average(vec);
  std::cout << "The average is: " << average << std::endl;
  auto now = dtr::now();
  std::cout << "Time since epoch is: " << now << std::endl;
}
