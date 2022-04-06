#ifndef AFENGINE_FOUNDATION_RUNTIME_H
#define AFENGINE_FOUNDATION_RUNTIME_H

#include <folly/Singleton.h>

#include <functional>

#include "../../macros/macros.h"
#include "internal/internal.h"

namespace afengine::foundation {
/**
 * The runtime environment
 */
class AFENGINE_EXPORT Runtime final {
  public:
    template <typename ReturnType>
    using AcquireCallback = std::function<ReturnType(Runtime&)>;

    template <typename ReturnType,
              typename Tag = internal::DefaultRuntimeSingletonTag,
              typename VaultTag = Tag>
    requires(!std::is_void_v<ReturnType>) static auto Acquire(
        const AcquireCallback<ReturnType>& callback)
        -> std::optional<ReturnType> {
      using ResultType = std::optional<ReturnType>;

      auto instance = folly::Singleton<Runtime, Tag, VaultTag>::try_get();
      if (instance == nullptr) {
        return std::nullopt;
      }

      auto result = callback(*instance);
      return ResultType{result};
    }

    template <typename ReturnType,
              typename Tag = internal::DefaultRuntimeSingletonTag,
              typename VaultTag = Tag>
    requires std::is_void_v<ReturnType>
    static auto Acquire(const AcquireCallback<ReturnType>& callback) -> bool {
      auto instance = folly::Singleton<Runtime, Tag, VaultTag>::try_get();
      if (instance == nullptr) {
        return false;
      }

      callback(*instance);
      return true;
    }

    AFENGINE_NO_EXPORT static auto Create() -> Runtime*;
    AFENGINE_NO_EXPORT static auto Teardown(Runtime*) -> void;

    auto Start() -> int;
    auto Shutdown() -> Runtime&;

  private:
    Runtime() = default;
};

}  // namespace afengine::foundation

#endif
