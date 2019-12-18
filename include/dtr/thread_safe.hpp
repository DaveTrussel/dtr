#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

namespace dtr {

template <typename T> class Safe_queue {
  using value_type = T;
  std::queue<T> queue_{};
  std::condition_variable cond_{};
  mutable std::mutex mutex_{};

public:
  void push(T &&value) {
    std::scoped_lock scoped(mutex_);
    queue_.push(std::forward<T>(value));
    cond_.notify_one();
  }

  void push(const T &value) {
    std::scoped_lock scoped(mutex_);
    queue_.push(value);
    cond_.notify_one();
  }

  T pop() {
    std::unique_lock lock(mutex_);
    cond_.wait(lock, [this] { return not queue_.empty(); });
    auto ret = queue_.front();
    queue_.pop();
    return ret;
  }

  template <typename Rep, typename Period>
  std::optional<T> pop(const std::chrono::duration<Rep, Period> &rel_time) {
    std::unique_lock lock(mutex_);
    bool success =
        cond_.wait_for(lock, rel_time, [this] { return not queue_.empty(); });
    std::optional<T> ret;
    if (success) {
      ret = queue_.front();
      queue_.pop();
    }
    return ret;
  }

  std::size_t size() const {
    std::scoped_lock scoped(mutex_);
    return queue_.size();
  }
};

} // namespace dtr
