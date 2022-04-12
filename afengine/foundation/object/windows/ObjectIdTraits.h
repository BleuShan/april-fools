#ifndef AFENGINE_FOUNDATION_OBJECT_WINDOWS_OBJECIDTTRAITS_H
#define AFENGINE_FOUNDATION_OBJECT_WINDOWS_OBJECIDTTRAITS_H

#include <winrt/Windows.Foundation.h>

#include "../constants.h"

using winrt::Windows::Foundation::GuidHelper;

namespace afengine::foundation {

using Uuid = winrt::guid;

template <>
struct ObjectIdTraits<Uuid> : TypeInfo<Uuid> {
    static auto parse(StringView value) -> ObjectIdTraits::value_type {
      const auto sourceSize = value.size();

      if (sourceSize == kCStrSize || sourceSize == kCStrLen) {
        const String data{value};
        return ObjectIdTraits::value_type{data};
      }

      if (sourceSize == kShortUuidStringLen ||
          sourceSize == kShortUuidStringSize) {
        std::array<StringView::value_type, kCStrSize> buffer{};
        auto reader = value.cbegin();
        const auto readerEnd = value.cend();

        auto writer = buffer.begin();
        auto writerEnd = buffer.cend();

        for (auto&& size : kUuidStringSegmentLengths) {
          writer = std::copy_n(reader, size, writer);
          reader = std::ranges::next(reader, size, readerEnd);

          if (reader != readerEnd && writer != writerEnd) {
            *writer = kDashChar;
            writer = std::ranges::next(writer, 1, writerEnd);
          }
        }
        const StringView result{buffer.data(), kCStrLen};
        return ObjectIdTraits::value_type{result};
      }

      throw std::invalid_argument("received an invalid uuid string");
    }

    static auto generate() -> ObjectIdTraits::value_type {
      return GuidHelper::CreateNewGuid();
    }

    static auto toString(ObjectIdTraits::const_reference value) -> String {
      return std::format(kGuidFormat, value.Data1, value.Data2, value.Data3,
                         value.Data4[0], value.Data4[1], value.Data4[2],
                         value.Data4[3], value.Data4[4], value.Data4[5],
                         value.Data4[6], value.Data4[7]);
    }

    static auto isNull(ObjectIdTraits::const_reference value) noexcept -> bool {
      return GuidHelper::Equals(value, GuidHelper::Empty());
    }
};

}  // namespace afengine::foundation

#endif