#include <afengine/foundation/object/id/internal/ObjectId.h>
#include <uuid/uuid.h>

#include <numeric>
#include <stdexcept>

namespace afengine::foundation::internal {

constexpr static const auto kDataSize = sizeof(uuid_t);
constexpr static const auto kCStrSize = sizeof(uuid_string_t);
constexpr static const auto kCStrLen = kCStrSize - 1;
constexpr static const auto kUuidStringSegmentLengths =
    std::array<size_t, 5>{8, 4, 4, 4, 12};
constexpr static const auto kShortUuidStringLen = std::accumulate(
    kUuidStringSegmentLengths.begin(), kUuidStringSegmentLengths.end(), 0ul);
constexpr static const auto kShortUuidStringSize = kShortUuidStringLen + 1;

ObjectId::ObjectId() {
  uuid_generate_random(reinterpret_cast<uint8_t*>(uuid_.data()));
}

ObjectId::ObjectId(const ObjectId& source) {
  std::copy(source.uuid_.begin(), source.uuid_.end(), uuid_.begin());

  if (source.cstr_ != nullptr) {
    cstr_ = new char[kDataSize];
    std::memcpy(cstr_, source.cstr_, kCStrSize);
  }
}

ObjectId::ObjectId(ObjectId&& source) noexcept
    : uuid_{std::move(source.uuid_)} {}

ObjectId::ObjectId(const std::string_view value) {
  auto sourceSize = source.size();
  auto sourceData = source.data();
  if (sourceSize == kCStrSize || sourceSize == kCStrLen) {
    auto size = std::max(source.size(), kCStrSize);
    cstr_ = new char[kCStrSize];
    strcpy(cstr_, sourceData);
  }

  if (cstr_ == nullptr && (sourceSize == kShortUuidStringLen ||
                           sourceSize == kShortUuidStringSize)) {
    cstr_ = new char[kCStrSize];
    size_t offset = 0;
    size_t sourceOffset = 0;
    for (auto&& size : kUuidStringSegmentLengths) {
      std::memcpy(&cstr_[offset], &sourceData[sourceOffset], size);
      sourceOffset += size;
      offset += size;
      cstr_[offset] = offset < kShortUuidStringLen ? '-' : '\0';
      offset += 1;
    }
  }

  if (cstr_ == nullptr) {
    throw new std::invalid_argument("value is not a valid uuid string");
  }

  if (cstr_ != nullptr) {
    uuid_parse(cstr_, reinterpret_cast<uint8_t*>(uuid_.data()));
  }
}

ObjectId::~ObjectId() {
  static_assert(sizeof(uuid_) == kDataSize);
  if (cstr_ != nullptr) {
    delete[] cstr_;
  }
}

ObjectId::operator String() {
  return String{cstr()};
}

ObjectId::operator StringView() {
  return StringView{cstr()};
}

auto ObjectId::operator=(const ObjectId& source) -> ObjectId& {
  std::copy(source.uuid_.begin(), source.uuid_.end(), uuid_.begin());
  if (source.cstr_ != nullptr) {
    cstr_ = cstr_ == nullptr ? new char[kDataSize] : cstr_;
    std::memcpy(cstr_, source.cstr_, kCStrSize);
  }
  return *this;
}

auto ObjectId::operator=(ObjectId&& source) -> ObjectId& {
  uuid_ = std::move(source.uuid_);
  if (cstr_ != nullptr) {
    delete[] cstr_;
    cstr_ = nullptr;
  }
  return *this;
}

auto ObjectId::cstr() -> const char* {
  if (cstr_ == nullptr) {
    cstr_ = new char[kCStrSize];
    uuid_unparse(reinterpret_cast<uint8_t*>(uuid_.data()), cstr_);
  }
  return cstr_;
}

auto ObjectId::IsNull() const noexcept -> bool {
  return uuid_is_null(reinterpret_cast<const uint8_t*>(uuid_.data())) == 1;
}

auto operator==(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(lhs.uuid_.data()),
                      reinterpret_cast<const uint8_t*>(rhs.uuid_.data())) == 0;
}

auto operator!=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(lhs.uuid_.data()),
                      reinterpret_cast<const uint8_t*>(rhs.uuid_.data())) != 0;
}

auto operator<(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(lhs.uuid_.data()),
                      reinterpret_cast<const uint8_t*>(rhs.uuid_.data())) < 0;
}

auto operator>(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(lhs.uuid_.data()),
                      reinterpret_cast<const uint8_t*>(rhs.uuid_.data())) > 0;
}

auto operator<=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(lhs.uuid_.data()),
                      reinterpret_cast<const uint8_t*>(rhs.uuid_.data())) <= 0;
}

auto operator>=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(lhs.uuid_.data()),
                      reinterpret_cast<const uint8_t*>(rhs.uuid_.data())) >= 0;
}
}  // namespace afengine::foundation::internal
