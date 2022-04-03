#ifndef AFENGINE_FOUNDATION_RUNTIME_H
#define AFENGINE_FOUNDATION_RUNTIME_H

#include <afengine/export-macros.h>
#include <afengine/foundation/runtime/internal/internal.h>
#include <folly/Singleton.h>

#include <functional>

namespace afengine::foundation {
/**
 * The runtime environment
 */
class AFENGINE_EXPORT Runtime final {
  public:
    template <typename ReturnType>
    using AcquireCallback = std::function<ReturnType(const Runtime&)>;

    template <typename ReturnType,
              typename Tag = internal::DefaultRuntimeSingletonTag,
              typename VaultTag = Tag>
    static auto Acquire(const AcquireCallback<ReturnType>& callback)
        -> std::optional<ReturnType> {
      using ResultType = std::optional<ReturnType>;

      auto instance = folly::Singleton<Runtime, Tag, VaultTag>::try_get();
      if (instance == nullptr) {
        return ResultType {};
      }

      auto result = callback(*instance);
      return ResultType{result};
    }

    AFENGINE_NO_EXPORT static auto Create() -> Runtime*;
    AFENGINE_NO_EXPORT static auto Teardown(Runtime*) -> void;

    auto Shutdown() -> Runtime&;

  private:
    Runtime() = default;
};

namespace internal {}

}  // namespace afengine::foundation

#endif
