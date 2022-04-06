#include "afengine/macros.h"
#include "../internal.h"

using winrt::Windows::Foundation::GuidHelper;

namespace afengine::foundation::internal {

auto ObjectIdHooks::Parse(StringView value) -> ValueTypeInfo::value_type {
  auto sourceSize = value.size();

  if (sourceSize == kCStrSize || sourceSize == kCStrLen) {
    const String data{value};
    return ValueTypeInfo::value_type{data};
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
        *writer = kDashChar;
        writer = std::ranges::next(writer, 1, writerEnd);
      }
    }
    StringView result{buffer};
    return ValueTypeInfo::value_type{result};
  }

  throw std::invalid_argument("received an invalid uuid string");
}

auto ObjectIdHooks::Generate() -> ValueTypeInfo::value_type {
  return GuidHelper::CreateNewGuid();
}

auto ObjectIdHooks::ToString(ValueTypeInfo::const_reference value) -> String {
  return std::format(kGuidFormat, value.Data1, value.Data2, value.Data3,
                            value.Data4[0], value.Data4[1], value.Data4[2],
                            value.Data4[3], value.Data4[4], value.Data4[5],
                            value.Data4[6], value.Data4[7]);
}

auto ObjectIdHooks::IsNull(ValueTypeInfo::const_reference value) noexcept
  return GuidHelper::Equals(Value(), GuidHelper::Empty());
}

auto operator==(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator!=(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return !GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator<(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return lhs.value_ < rhs.value_;
}

auto operator<=(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return lhs.value_ < rhs.value_ || GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator>(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return !(lhs.value_ < rhs.value_);
}

auto operator>=(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return !(lhs.value_ < rhs.value_) &&
         !GuidHelper::Equals(lhs.value_, rhs.value_);
}
}  // namespace afengine::foundation::internal
