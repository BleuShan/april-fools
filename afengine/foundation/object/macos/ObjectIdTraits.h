#ifndef AFENGINE_FOUNDATION_OBJECT_MACOS_OBJECIDTTRAITS_H
#define AFENGINE_FOUNDATION_OBJECT_MACOS_OBJECIDTTRAITS_H

#include <uuid/uuid.h>

#include <algorithm>
#include <array>
#include <numeric>
#include <stdexcept>

#include "../constants.h"

namespace afengine::foundation {
using Uuid = std::array<uint8_t, kObjectIdValueMaxSize>;

template <>
struct ObjectIdTraits<Uuid> : TypeInfo<Uuid> {
    static auto toString(ObjectIdTraits::const_reference value) -> String {
      std::array<String::value_type, kCStrSize> buffer{};
      uuid_unparse(value.data(), buffer.data());
      return String{buffer.data()};
    }

    static auto parse(StringView value) -> ObjectIdTraits::value_type {
      auto sourceSize = value.size();
      bool success = false;
      ObjectIdTraits::value_type result{};
      if (sourceSize == kCStrSize || sourceSize == kCStrLen) {
        String data{value};
        success = uuid_parse(data.data(), result.data()) == 0;
      }

      if (!success && (sourceSize == kShortUuidStringLen ||
                       sourceSize == kShortUuidStringSize)) {
        std::array<StringView::value_type, kCStrSize> buffer{};
        auto reader = value.cbegin();
        auto writer = buffer.begin();
        auto writerEnd = buffer.cend();
        auto readerEnd = value.cend();

        for (auto&& size : kUuidStringSegmentLengths) {
          auto segmentEnd = std::ranges::next(reader, size, readerEnd);
          std::transform(
              reader, segmentEnd, writer,
              [](StringView::value_type ch) { return std::tolower(ch); });
          reader = segmentEnd;
          writer = std::ranges::next(writer, size, writerEnd);

          if (reader != readerEnd && writer != writerEnd) {
            *writer = kDashChar;
            writer = std::ranges::next(writer, 1, writerEnd);
          }
        }

        success = uuid_parse(buffer.data(), result.data()) == 0;
      }

      if (!success) {
        throw std::invalid_argument(
            fmt::format("\"{}\" is not a valid uuid string", value));
      }

      return result;
    }

    static auto generate() -> ObjectIdTraits::value_type {
      ObjectIdTraits::value_type result{};
      uuid_generate_random(result.data());

      return result;
    }

    static auto isNull(ObjectIdTraits::const_reference value) noexcept -> bool {
      return uuid_is_null(value.data()) == 1;
    }
};

}  // namespace afengine::foundation

#endif