#ifndef AFENGINE_RUNTIME_CONCURRENT_WORKERPOOL_H
#define AFENGINE_RUNTIME_CONCURRENT_WORKERPOOL_H

#include <absl/container/btree_map.h>

#include "Worker.h"
#include "afengine/foundation/traits/Singleton.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::concurrent {

class AFENGINE_EXPORT WorkerPool final
    : public foundation::Singleton<WorkerPool>,
      public std::enable_shared_from_this<WorkerPool> {
  public:
    auto initialize() -> WorkerPool&;

  private:
    friend Holder;
    WorkerPool() noexcept = default;
    size_t capacity_ = std::thread::hardware_concurrency();
    absl::btree_map<Worker::Id, Worker::SharedPtr> workers_{};
};

}  // namespace afengine::runtime::concurrent

#endif  // AFENGINE_RUNTIME_CONCURRENT_THREADPOOL_H
