#ifndef AFENGINE_RUNTIME_PLATFORM_WINDOWS_PLATFORM_H
#define AFENGINE_RUNTIME_PLATFORM_WINDOWS_PLATFORM_H

#include "../core/core.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::platform::windows {

class AFENGINE_EXPORT Platform final : public core::Platform {
    auto platformInitialize() -> void override;
    auto platformRun() -> int override;
    auto platformShutdown() -> void override;
    [[nodiscard]] auto platformProcessInfo() const
        -> core::ProcessInfo override;
};

}  // namespace afengine::runtime::platform::windows
#endif  // AFENGINE_RUNTIME_PLATFORM_WINDOWS_PLATFORM_H
