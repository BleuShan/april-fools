#ifndef AFENGINE_FOUNDATION_TRAITS_SINGLETON_H
#define AFENGINE_FOUNDATION_TRAITS_SINGLETON_H

#include <folly/Singleton.h>

namespace afengine::foundation {

template <typename Derived>
class Singleton {
  public:
    using Holder = folly::Singleton<Derived>;

    static auto instance() -> Derived& {
      const auto instance = Holder::try_get();
      if (instance == nullptr) {
        throw std::logic_error{"instance was destroyed."};
      }

      auto result = instance.get();
      if (result == nullptr) {
        throw std::logic_error("Could not access instance reference");
      }

      return *result;
    }
};

}  // namespace afengine::foundation

#endif  // AFENGINE_FOUNDATION_TRAITS_SINGLETON_H
