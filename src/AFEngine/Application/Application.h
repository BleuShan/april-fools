#ifndef AFENGINE_APPLICATION_H
#define AFENGINE_APPLICATION_H

#include <AFEngine/export_macros.h>

#include <AFEngine/Foundation/Object.h>

#include <functional>

namespace AFEngine {
class AFENGINE_API Application final : public Foundation::Object<Application> {
 public:
  static auto instance() -> SharedPtr;

  auto configure() -> const Application&;

  
  AFENGINE_PRIVATE static auto create() -> Application*;
  AFENGINE_PRIVATE static auto teardown(Application* app) -> void;
 private:
  Application() = default;
  bool running_;

};

}  // namespace AFEngine

#endif
