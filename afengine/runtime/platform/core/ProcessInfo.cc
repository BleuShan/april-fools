#include "ProcessInfo.h"

namespace fs = std::filesystem;

namespace afengine::runtime::platform::core {

auto ProcessInfo::currentPath() const -> FSPath {
  return fs::current_path();
}

[[nodiscard]] auto ProcessInfo::executableDirectory() const -> FSPath {
  return executablePath.parent_path();
};

}  // namespace afengine::runtime::platform::core