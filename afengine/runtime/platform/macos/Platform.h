#ifndef AFENGINE_RUNTIME_PLATFORM_MACOS_PLATFORM_H
#define AFENGINE_RUNTIME_PLATFORM_MACOS_PLATFORM_H

#include "../core/core.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::platform::macos {

class AFENGINE_EXPORT Platform final : public core::Platform {
  protected:
    auto Initialize() -> void override;
    auto Main() -> int override;
    auto Terminate(bool notify) -> void override;
    auto GetCommandLineArguments() const
        -> std::vector<foundation::StringView> override;
};

}  // namespace afengine::runtime::platform::macos

#endif  // AFENGINE_RUNTIME_PLATFORM_MACOS_PLATFORM_H
