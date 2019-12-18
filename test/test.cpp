#include "dtr/math/math.hpp"
#include "dtr/thread_safe.hpp"
#include "dtr/time/time.hpp"

#include <iostream>
#include <thread>
#include <vector>

int some_function(int init) {
  int sum = init;
  for (int i = 0; i < 1e6; ++i) {
    sum += i;
  }
  return sum;
}

int global_int = 0;

int main() {
  std::function<int(int)> intfunc = [](int abc) { return abc + 1; };
  std::function<void(int)> voidfunc = [](int abc) { global_int += abc; };
  std::function adapter = some_function;

  std::vector<double> vec{5, 6, 4, 3, 2, 6, 7, 9, 3, 1.5};
  auto median = dtr::median(vec);
  std::cout << "The median is: " << median << std::endl;
  auto average = dtr::average(vec);
  std::cout << "The average is: " << average << std::endl;
  auto now = dtr::now();
  std::cout << "Time since epoch is: " << now << std::endl;
  auto res = dtr::benchmark(100, intfunc, 3);
  std::cout << "Benchmark result is: " << res << std::endl;
  res = dtr::benchmark(100, voidfunc, 100);
  std::cout << "Benchmark result is: " << res << std::endl;
  res = dtr::benchmark(100, some_function, 0);
  std::cout << "Benchmark result is: " << res << std::endl;

  dtr::Safe_queue<int> queue;

  std::thread consumer([&] {
    int value = -1;
    while (1042 != value) {
      value = queue.pop();
    }
    std::cout << "Done consuming. " << std::endl;
  });

  for (int i = 0; i < 1337; ++i) {
    queue.push(i);
  }

  consumer.join();
  std::cout << "Remaining queue size " << queue.size() << std::endl;

  std::cout << "Timed pop: " << *queue.pop(std::chrono::milliseconds(100))
            << std::endl;
}
