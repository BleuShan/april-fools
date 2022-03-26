#ifndef AFENGINE_APPLICATION_H
#define AFENGINE_APPLICATION_H

#include <AFEngine/export_macros.h>

#include <AFEngine/Foundation/Object.h>

namespace AFEngine {
class AFENGINE_API Application final : public Foundation::Object<Application> {
 public:
  AFENGINE_PRIVATE static auto create() -> Application*;
  static auto instance() -> SharedPtr;

 private:
  Application() = default;
};

}  // namespace AFEngine

#endif
