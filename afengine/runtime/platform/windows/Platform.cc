#include "Platform.h"

#include <mddbootstrap.h>

#include "common.h"

namespace afengine::runtime::platform::windows {

auto Platform::platformInitialize() -> void {
  winrt::init_apartment();
}

auto Platform::platformRun() -> int {
  return 0;
}

auto Platform::platformShutdown() -> void {
  winrt::clear_factory_cache();
  winrt::uninit_apartment();
}

auto Platform::platformProcessInfo() const -> core::ProcessInfo {
  std::vector<foundation::StdStringView> args{};
  foundation::StdStringView commandLine{GetCommandLineA()};
  auto argStart = commandLine.cbegin();
  auto argEnd = commandLine.cbegin();
  const auto end = commandLine.cend();
  while (argEnd != end) {
    auto next = std::ranges::next(argEnd, 1, end);
    if (*next == ' ' && next != end) {
      args.emplace_back(argStart, argEnd);
      argStart = argEnd;
    }

    argEnd = next;
  }

  if (args.empty()) {
    args.emplace_back(commandLine);
  }

  return args;
}

}  // namespace afengine::runtime::platform::windows
