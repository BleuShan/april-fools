#ifndef AFENGINE_APPLICATION_H
#define AFENGINE_APPLICATION_H

#include <afengine/export-macros.h>

#include <afengine/foundation/object/Object.h>

#include <functional>

namespace afengine {
class AFENGINE_EXPORT Application final
    : public foundation::Object<Application> {
 public:
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
