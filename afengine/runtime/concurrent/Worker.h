#ifndef AFENGINE_RUNTIME_CONCURRENT_WORKER_H
#define AFENGINE_RUNTIME_CONCURRENT_WORKER_H

#include <thread>

#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::concurrent {

class WorkerPool;

class AFENGINE_EXPORT Worker final
    : public std::enable_shared_from_this<Worker> {
  public:
    using Id = std::thread::id;
    using SharedPtr = std::shared_ptr<Worker>;

    ~Worker();

    static auto create(std::weak_ptr<WorkerPool> parent) -> SharedPtr {
      return SharedPtr{new Worker{std::move(parent)}};
    }

    [[nodiscard]] auto id() const -> Id { return thread_.get_id(); };

  private:
    explicit Worker(std::weak_ptr<WorkerPool> parent)
        : parent_{std::move(parent)} {}
    std::thread thread_{};
    std::weak_ptr<WorkerPool> parent_;
};

}  // namespace afengine::runtime::concurrent

#endif  // AFENGINE_RUNTIME_CONCURRENT_WORKER_H
