#include "Worker.h"

namespace afengine::runtime::concurrent {

Worker::~Worker() {
  if (thread_.joinable()) {
    thread_.join();
  }
}

}  // namespace afengine::runtime::concurrent