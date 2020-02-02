#pragma once

#include <string>

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace dtr {
namespace ipc {

namespace bip = boost::interprocess;

template <typename T, bool IS_CREATOR> class Vector {
  using value_type = T;
  using ShmemAllocator =
      bip::allocator<T,bip::managed_shared_memory::segment_manager>;
  using MyVector = bip::vector<T, ShmemAllocator>;

  bip::managed_shared_memory segment_;
  MyVector *vector_ = nullptr;

public:
  Vector(const std::string &name)
      : segment_(bip::open_or_create, (name + "-segment").c_str(), 65536) {
    if constexpr (IS_CREATOR) {
      const ShmemAllocator allocator(segment_.get_segment_manager());
      vector_ = segment_.construct<MyVector>((name + "-vector").c_str())(allocator);
    } else {
      vector_ = segment_.find<MyVector>((name + "-vector").c_str()).first;
    }
  }

  Vector(const Vector&) = delete;
  Vector operator=(const Vector&) = delete;
};

} // namespace ipc
} // namespace dtr
