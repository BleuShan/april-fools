#ifndef AFENGINE_FOUNDATION_TYPES_COROUTINE_H
#define AFENGINE_FOUNDATION_TYPES_COROUTINE_H

#if __has_include(<coroutine>)
  #include <coroutine>
#elif __has_include(<experimental/coroutine>)
  #include <experimental/coroutine>

namespace std {

using std::experimental::coroutine_handle;
using std::experimental::coroutine_traits;
using std::experimental::noop_coroutine;
using std::experimental::noop_coroutine_handle;
using std::experimental::noop_coroutine_promise;
using std::experimental::suspend_always;
using std::experimental::suspend_never;

}  // namespace std

#else
  #error "No r"
#endif

#endif  // AFENGINE_RUNTIME_CONCURRENT_COROUTINE_H
