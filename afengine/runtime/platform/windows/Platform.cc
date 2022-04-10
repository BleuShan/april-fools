#include "Platform.h"
#include "common.h"
#include <mddbootstrap.h>

namespace afengine::runtime::platform::windows {

auto Platform::PlatformBootstrap() -> void {
  winrt::init_apartment();
}

auto Platform::PlatformRun() -> int {
  return 0;
}

auto Platform::PlatformShutdown() -> void {
  winrt::clear_factory_cache();
  winrt::uninit_apartment();
}

auto Platform::PlatformCommandlineArguments() const
    -> std::vector<foundation::StdStringView> {
  std::vector<foundation::StdStringView> args{};
  foundation::StdStringView commandLine{GetCommandLineA()};
  auto argStart = commandLine.cbegin();
  auto argEnd = commandLine.cbegin();
  const auto end = commandLine.cend();
  while(argEnd != end) {
    auto next = std::ranges::next(argEnd, 1, end);
    if ( *next == ' ' && next != end) {
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

}
