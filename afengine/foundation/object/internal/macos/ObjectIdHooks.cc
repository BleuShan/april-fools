#include "ObjectIdHooks.h"

#include <uuid/uuid.h>

#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace afengine::foundation::internal {

auto ObjectIdHooks::ToString(ValueTypeInfo::const_reference value) -> String {
  std::array<String::value_type, kCStrSize> buffer{};
  uuid_unparse(value.data(), buffer.data());
  return String{buffer.data()};
}

auto ObjectIdHooks::Parse(StringView value) -> ValueTypeInfo::value_type {
  auto sourceSize = value.size();
  bool success = false;
  ValueTypeInfo::value_type result{};
  if (sourceSize == kCStrSize || sourceSize == kCStrLen) {
    String data{value};
    success = uuid_parse(data.data(), result.data()) == 0;
  }

  if (!success && (sourceSize == kShortUuidStringLen ||
                   sourceSize == kShortUuidStringSize)) {
    std::array<StringView::value_type, kCStrSize + 1> buffer{};
    auto reader = value.cbegin();
    auto writer = buffer.begin();
    auto writerEnd = buffer.cend();
    auto readerEnd = value.cend();

    for (auto&& size : kUuidStringSegmentLengths) {
      auto segmentEnd = std::ranges::next(reader, size, readerEnd);
      std::transform(reader, segmentEnd, writer, std::tolower);
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

auto ObjectIdHooks::Generate() -> ValueTypeInfo::value_type {
  ValueTypeInfo::value_type result{};
  uuid_generate_random(result.data());

  return result;
}

auto ObjectIdHooks::IsNull(ValueTypeInfo::const_reference value) noexcept
    -> bool {
  return uuid_is_null(value.data()) == 1;
}

auto operator==(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) == 0;
}

auto operator!=(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) != 0;
}

auto operator<(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) < 0;
}

auto operator>(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) > 0;
}

auto operator<=(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) <= 0;
}

auto operator>=(
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& lhs,
    const BasicObjectId<ObjectIdHooks::ValueTypeInfo, ObjectIdHooks>& rhs)
    -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) >= 0;
}
}  // namespace afengine::foundation::internal
