#ifndef AFENGINE_FOUNDATION_OBJECT_OBJECTIDTRAITS_H
#define AFENGINE_FOUNDATION_OBJECT_OBJECTIDTRAITS_H

#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"

namespace afengine::foundation {

template <typename ValueT>
struct ObjectIdTraits : TypeInfo<ValueT> {};

template <std::integral ValueT>
struct ObjectIdTraits<ValueT> : TypeInfo<ValueT> {
    static auto parse(StringView value) -> typename ObjectIdTraits::value_type {
      typename ObjectIdTraits::value_type result{};
      auto [ptr, ec] = std::from_chars(value.begin(), value.end(), result);
      if (ec != std::errc{}) {
        auto code = std::make_error_code(ec);
        throw std::system_error{code};
      }

      return result;
    }

    static auto isNull(typename ObjectIdTraits::const_reference value) noexcept
        -> bool {
      return value == nullptr || value == 0;
    }

    static auto toString(typename ObjectIdTraits::const_reference value)
        -> String {
      return std::to_string(value);
    }
};

}  // namespace afengine::foundation

#if TARGET_OS_WINDOWS
  #include "windows/ObjectIdTraits.h"
#elif TARGET_OS_MACOS
  #include "macos/ObjectIdTraits.h"
#endif

#endif  // AFENGINE_FOUNDATION_OBJECT_INTERNAL_OBJECTIDTRAITS_H
