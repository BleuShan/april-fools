#ifndef AFENGINE_RUNTIME_PLATFORM_CORE_PROCESSINFO_H
#define AFENGINE_RUNTIME_PLATFORM_CORE_PROCESSINFO_H

#include <filesystem>
#include <vector>

#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::platform::core {

struct AFENGINE_EXPORT ProcessInfo final {
    const foundation::StdString processName;
    const FSPath executablePath;
    const std::vector<foundation::StdString> commandLineArguments;

    [[nodiscard]] auto currentPath() const -> FSPath;
    [[nodiscard]] auto executableDirectory() const -> FSPath;
};

}  // namespace afengine::runtime::platform::core
#endif
