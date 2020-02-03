#pragma once

#include <functional>

namespace dtr {

/// type erased version of a scope guard
class ScopeGuard {
    public:
    template <typename Func> ScopeGuard(Func&& func) : commit_(false), func_(func) {}
    template <typename Func> ScopeGuard(const Func& func) : commit_(false), func_(func) {}
    ~ScopeGuard() { if (!commit_) func_(); }
    void commit() const noexcept { commit_ = true; }
    ScopeGuard(ScopeGuard&& other) : commit_(other.commit_), func_(other.func_) { other.commit(); }
    private:
    mutable bool commit_;
    std::function<void()> func_;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
};

} // namespace dtr
