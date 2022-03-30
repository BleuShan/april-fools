#ifndef AFENGINE_APPLICATION_H
#define AFENGINE_APPLICATION_H

#include <afengine/export-macros.h>
#include <afengine/foundation/object/Object.h>

#include <functional>
#include <memory>

namespace afengine {
class AFENGINE_EXPORT Application final : public foundation::Object {
 public:
  /**
   * Alias for the shared pointer type
   */
  using SharedPtr = std::shared_ptr<Application>;
  /**
   * Alias for the weak pointer type
   */
  using WeakPtr = std::weak_ptr<Application>;

  auto operator=(const Application& other) -> Application& { return *this; }

  static auto instance() -> SharedPtr;

  AFENGINE_NO_EXPORT static auto create() -> Application*;
  AFENGINE_NO_EXPORT static auto teardown(Application* app) -> void;

 private:
  Application() = default;

  bool running_ = false;
};

}  // namespace afengine

#endif
