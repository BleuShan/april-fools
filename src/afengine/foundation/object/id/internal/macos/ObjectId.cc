#include <afengine/foundation/object/id/internal/ObjectId.h>
#include <uuid/uuid.h>

#include <numeric>
#include <utility>

using afengine::foundation::internal::ObjectId;

constexpr static const auto kDataSize = sizeof(uuid_t);
constexpr static const auto kCStrSize = sizeof(uuid_string_t);
constexpr static const auto kCStrLen = kCStrSize - 1;
constexpr static const auto kUuidStringSegmentLengths =
    std::array<size_t, 5>{8, 4, 4, 4, 12};
constexpr static const auto kShortUuidStringLen = std::accumulate(
    kUuidStringSegmentLengths.begin(), kUuidStringSegmentLengths.end(), 0ul);
constexpr static const auto kShortUuidStringSize = kShortUuidStringLen + 1;

ObjectId::ObjectId() {
  static_assert(sizeof(ObjectId::uuid_) == kDataSize);
  uuid_generate_random(reinterpret_cast<uint8_t*>(uuid_.data()));
}

ObjectId::ObjectId(const ObjectId& source) {
  std::copy(source.uuid_.begin(), source.uuid_.end(), uuid_.begin());

  if (source.cstr_ != nullptr) {
    cstr_ = new char[kDataSize];
    std::memcpy(cstr_, source.cstr_, kCStrSize);
  }
}

ObjectId::ObjectId(const std::string_view source) {
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

  if (cstr_ != nullptr) {
    uuid_parse(cstr_, reinterpret_cast<uint8_t*>(uuid_.data()));
  }
}

ObjectId::ObjectId(ObjectId&& source) : uuid_{std::move(source.uuid_)} {}

ObjectId::~ObjectId() {
  if (cstr_ != nullptr) {
    delete[] cstr_;
  }
}

ObjectId::operator std::string() {
  return std::string{cstr()};
}

ObjectId::operator std::string_view() {
  return std::string_view{cstr()};
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

auto ObjectId::operator==(const ObjectId& other) const -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(uuid_.data()),
                      reinterpret_cast<const uint8_t*>(other.uuid_.data())) ==
         0;
}

auto ObjectId::operator!=(const ObjectId& other) const -> bool {
  return !(*this == other);
}

auto ObjectId::operator<(const ObjectId& other) const -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(uuid_.data()),
                      reinterpret_cast<const uint8_t*>(other.uuid_.data())) < 0;
}

auto ObjectId::operator>(const ObjectId& other) const -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(uuid_.data()),
                      reinterpret_cast<const uint8_t*>(other.uuid_.data())) > 0;
}

auto ObjectId::operator<=(const ObjectId& other) const -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(uuid_.data()),
                      reinterpret_cast<const uint8_t*>(other.uuid_.data())) <=
         0;
}

auto ObjectId::operator>=(const ObjectId& other) const -> bool {
  return uuid_compare(reinterpret_cast<const uint8_t*>(uuid_.data()),
                      reinterpret_cast<const uint8_t*>(other.uuid_.data())) >=
         0;
}

auto ObjectId::isNull() const noexcept -> bool {
  return uuid_is_null(reinterpret_cast<const uint8_t*>(uuid_.data())) == 1;
}

auto ObjectId::cstr() -> const char* {
  if (cstr_ == nullptr) {
    cstr_ = new char[kCStrSize];
    uuid_unparse(reinterpret_cast<uint8_t*>(uuid_.data()), cstr_);
  }
  return cstr_;
}
