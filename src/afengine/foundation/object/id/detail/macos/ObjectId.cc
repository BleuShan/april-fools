#include <afengine/foundation/object/id/detail/ObjectId.h>

#include <array>
#include <numeric>
#include <utility>

using afengine::foundation::detail::ObjectId;

constexpr static const auto kDataSize = sizeof(uuid_t);
constexpr static const auto kStringDataSize = sizeof(uuid_string_t);
constexpr static const auto kStringDataLength = kStringDataSize - 1;
constexpr static const auto kStringSegmentLengths =
    std::array<size_t, 5>{8, 4, 4, 4, 12};
constexpr static const auto kShortStringDataSize = std::accumulate(
    kStringSegmentLengths.begin(), kStringSegmentLengths.end(), 0ul);

ObjectId::ObjectId() {
  uuid_generate_random(data_);
}

ObjectId::ObjectId(const ObjectId& source) {
  uuid_copy(data_, source.data_);
  if (strlen(source.stringData_) != 0) {
    strcpy(stringData_, source.stringData_);
  }
}

ObjectId::ObjectId(const std::string_view source) {
  auto sourceSize = source.size();
  auto sourceData = source.data();
  if (sourceSize == kStringDataSize || sourceSize == (kStringDataSize - 1)) {
    auto size = std::max(source.size(), kStringDataSize);
    strcpy(stringData_, sourceData);
  }

  if (strlen(stringData_) == 0 && (sourceSize == kShortStringDataSize ||
                                   sourceSize == (kShortStringDataSize + 1))) {
    size_t offset = 0;
    size_t sourceOffset = 0;
    for (auto&& size : kStringSegmentLengths) {
      std::memcpy(&stringData_[offset], &sourceData[sourceOffset], size);
      sourceOffset += size;
      offset += size;
      stringData_[offset] = offset < kShortStringDataSize ? '-' : '\0';
      offset += 1;
    }
  }

  if (strlen(stringData_) == kStringDataLength) {
    uuid_parse(stringData_, data_);
  }
}

auto ObjectId::isNull() const -> bool {
  return uuid_is_null(data_);
}

ObjectId::operator std::string() {
  std::string_view sv = *this;
  return std::string{sv};
}

ObjectId::operator std::string_view() {
  if (strlen(stringData_) == 0) {
    uuid_unparse(data_, stringData_);
  }

  return std::string_view{
      stringData_,
  };
}

auto ObjectId::operator=(const ObjectId& source) -> ObjectId& {
  uuid_copy(data_, source.data_);
  uuid_unparse(data_, stringData_);
  return *this;
}

auto ObjectId::operator==(const ObjectId& other) const -> bool {
  return uuid_compare(data_, other.data_) == 0;
}

auto ObjectId::operator!=(const ObjectId& other) const -> bool {
  return uuid_compare(data_, other.data_) != 0;
}
