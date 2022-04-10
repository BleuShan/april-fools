#ifndef AFENGINE_RUNTIME_PLATFORM_WINDOWS_PLATFORM_H
#define AFENGINE_RUNTIME_PLATFORM_WINDOWS_PLATFORM_H

#include "../core/core.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::platform::windows {

class AFENGINE_EXPORT Platform final: public core::Platform {
    auto PlatformBootstrap() -> void override;
    auto PlatformRun() -> int override;
    auto PlatformShutdown() -> void override;
    [[nodiscard]] auto PlatformCommandlineArguments() const
        -> std::vector<foundation::StdStringView> override;
};

}  // namespace afengine::runtime::platform::windows
#endif  // AFENGINE_RUNTIME_PLATFORM_WINDOWS_PLATFORM_H
