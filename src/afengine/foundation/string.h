#ifndef AFENGINE_FOUNDATION_STRING_H
#define AFENGINE_FOUNDATION_STRING_H

#include <folly/FixedString.h>

#include <string>

namespace afengine{
using namespace std::literals;
}


namespace afengine::foundation {

#if UNICODE && WIN32
using String = std::wstring;
using StringView = std::wstring_view;
#else
using String = std::string;
using StringView = std::string_view;
#endif

template <typename StringLike,
          typename ReadableTrait = std::indirectly_readable_traits<StringLike>>
requires std::integral<typename StringLike::value_type> &&
    requires(StringLike& value) {
  { std::ranges::begin(value) } -> std::input_or_output_iterator;
  { std::ranges::end(value) } -> std::input_or_output_iterator;
}
constexpr auto IsEmptyOrBlank(StringLike value) noexcept -> bool {
  if (std::empty(value)) return true;
  return std::all_of(
      std::ranges::begin(value), std::ranges::end(value),
      [](typename ReadableTrait::value_type character) {
        if constexpr (std::is_same_v<typename StringLike::value_type,
                                     wchar_t>) {
          return std::iswblank(character) != 0;
        }
        return std::isblank(character) != 0;
      });
}

}  // namespace afengine::foundation

#endif
