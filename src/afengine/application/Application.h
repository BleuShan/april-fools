#ifndef AFENGINE_APPLICATION_H
#define AFENGINE_APPLICATION_H

#include <afengine/export_macros.h>

#include <afengine/foundation/Object.h>

#include <functional>

namespace afengine {
class AFENGINE_API Application final : public foundation::Object<Application> {
 public:
  auto operator=(const Application& other) -> Application& { return *this; }

  static auto instance() -> Application&;

  AFENGINE_PRIVATE static auto create() -> Application*;
  AFENGINE_PRIVATE static auto teardown(Application* app) -> void;

 private:
  Application() = default;

  bool running_ = false;
};

}  // namespace afengine

#endif
