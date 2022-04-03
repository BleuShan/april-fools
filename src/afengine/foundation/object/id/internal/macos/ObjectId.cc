#include <afengine/foundation/object/id/internal/internal.h>
#include <uuid/uuid.h>

#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace afengine::foundation::internal {

constexpr auto kCStrSize = sizeof(uuid_string_t);
constexpr auto kCStrLen = kCStrSize - 1;

ObjectId::operator String() const {
  std::array<String::value_type, kCStrSize> buffer{};
  uuid_unparse(Value().data(), buffer.data());
  return String{buffer.data()};
}

auto ObjectId::Parse(StringView value) -> ValueType {
  auto sourceSize = value.size();
  bool success = false;
  ValueType result{};
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
      writer = std::copy_n(reader, size, writer);
      reader = std::ranges::next(reader, size, readerEnd);

      if (reader != readerEnd && writer != writerEnd) {
        *writer = '-';
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

auto ObjectId::Generate() -> ValueType {
  ValueType result{};
  uuid_generate_random(result.data());

  return result;
}

auto ObjectId::IsNull() const noexcept -> bool {
  return uuid_is_null(Value().data()) == 1;
}

auto operator==(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) == 0;
}

auto operator!=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) != 0;
}

auto operator<(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) < 0;
}

auto operator>(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) > 0;
}

auto operator<=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) <= 0;
}

auto operator>=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) >= 0;
}
}  // namespace afengine::foundation::internal
