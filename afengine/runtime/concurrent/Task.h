#ifndef AFENGINE_RUNTIME_CONCURRENT_TASK_H
#define AFENGINE_RUNTIME_CONCURRENT_TASK_H

#include "afengine/foundation/types/types.h"

namespace afengine::runtime::concurrent {

template <typename Result>
class Task {
  public:
  private:
    LifeCycleState lifeCycle_;
};

}  // namespace afengine::runtime::concurrent

#endif  // AFENGINE_RUNTIME_CONCURRENT_TASK_H
