#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/internal/internal.h>
#include <fmt/format.h>

using winrt::Windows::Foundation::GuidHelper;

namespace afengine::foundation::internal {

#if UNICODE
constexpr StringView kGuidFormat =
    L"{:08x}-{:04x}-{:04x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}";
#else
constexpr StringView kGuidFormat =
    "{:08x}-{:04x}-{:04x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}";
#endif

constexpr auto kCStrLen =
    kShortUuidStringLen + kUuidStringSegmentLengths.size();
constexpr auto kCStrSize = kCStrLen + 1;

auto ObjectId::Parse(StringView value) -> ValueType {
  auto sourceSize = value.size();

  if (sourceSize == kCStrSize || sourceSize == kCStrLen) {
    const String data{value};
    return ValueType{data};
  }

  if (sourceSize == kShortUuidStringLen || sourceSize == kShortUuidStringSize) {
    std::array<StringView::value_type, kCStrSize> buffer{};
    auto reader = value.cbegin();
    auto readerEnd = value.cend();

    auto writer = buffer.begin();
    auto writerEnd = buffer.cend();

    for (auto&& size : kUuidStringSegmentLengths) {
      writer = std::copy_n(reader, size, writer);
      reader = std::ranges::next(reader, size, readerEnd);

      if (reader != readerEnd && writer != writerEnd) {
        *writer = '-';
        writer = std::ranges::next(writer, 1, writerEnd);
      }
    }
    StringView result{buffer};
    return ValueType{result};
  }

  throw std::invalid_argument("received an invalid uuid string");
}

auto ObjectId::Generate() -> ValueType {
  return GuidHelper::CreateNewGuid();
}

ObjectId::operator String() const {
  auto& value = Value();
  auto result = std::format(kGuidFormat, value.Data1, value.Data2, value.Data3,
                            value.Data4[0], value.Data4[1], value.Data4[2],
                            value.Data4[3], value.Data4[4], value.Data4[5],
                            value.Data4[6], value.Data4[7]);

  return result;
}

auto ObjectId::IsNull() const noexcept -> bool {
  return GuidHelper::Equals(Value(), GuidHelper::Empty());
}

auto operator==(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator!=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return !GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator<(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return lhs.value_ < rhs.value_;
}

auto operator<=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return lhs.value_ < rhs.value_ || GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator>(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return !(lhs.value_ < rhs.value_);
}

auto operator>=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return !(lhs.value_ < rhs.value_) &&
         !GuidHelper::Equals(lhs.value_, rhs.value_);
}
} // namespace afengine::foundation::internal
