#ifndef AFENGINE_FOUNDATION_STRING_H
#define AFENGINE_FOUNDATION_STRING_H

#include <folly/FixedString.h>

#include <charconv>
#include <cctype>
#include <string>

#if UNICODE && WIN32
  #include <cwctype>
#endif

namespace afengine {
using namespace std::literals;

namespace foundation {

using U8String = std::u8string;
using U8StringView  = std::u8string_view;
using U16String = std::u16string;
using U16StringView  = std::u16string_view;
using U32String = std::u32string;
using U32StringView  = std::u32string_view;
using StdString = std::string;
using StdStringView = std::string_view;

#if UNICODE && WIN32
using String = std::wstring;
using StringView = std::wstring_view;
#else
using String = StdString;
using StringView = StdStringView;
#endif


template <size_t size>
using FixedString [[maybe_unused]] = folly::BasicFixedString<String::value_type, size>;

template <typename StringLike>
requires std::integral<typename StringLike::value_type> &&
    requires(StringLike& value) {
  { std::ranges::begin(value) } -> std::input_or_output_iterator;
  { std::ranges::end(value) } -> std::input_or_output_iterator;
}
constexpr auto isEmptyOrBlank(StringLike value) noexcept -> bool {
  using ReadableTrait = std::indirectly_readable_traits<StringLike>;

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

}  // namespace foundation
}  // namespace afengine
#endif
