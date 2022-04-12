#include "WorkerPool.h"

namespace afengine::runtime::concurrent {

auto WorkerPool::initialize() -> WorkerPool& {
  if (!workers_.empty()) {
    return *this;
  }

  while (workers_.size() < capacity_) {
    auto weakThis = weak_from_this();
    auto worker = Worker::create(weakThis);
    workers_.insert_or_assign(worker->id(), worker);
  }

  return *this;
}

}  // namespace afengine::runtime::concurrent

namespace {

using afengine::runtime::concurrent::WorkerPool;

[[maybe_unused]] const WorkerPool::Holder defaultWorkerPool{};

}  // namespace