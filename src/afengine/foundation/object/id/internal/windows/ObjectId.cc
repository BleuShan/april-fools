#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/internal/windows/ObjectId.h>

using winrt::Windows::Foundation::GuidHelper;

namespace afengine::foundation::internal {
#if UNICODE
constexpr StringView kGuidFormat =
    L"{:08x}-{:04x}-{:04x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}";
#else
constexpr StringView kGuidFormat =
    "{:08x}-{:04x}-{:04x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}";
#endif

ObjectId::ObjectId() : guid_{GuidHelper::CreateNewGuid()} {}

ObjectId::ObjectId(const StringView data) : guid_{data} {}

ObjectId::operator String() const {
  auto result = std::format(kGuidFormat, guid_.Data1, guid_.Data2, guid_.Data3,
                            guid_.Data4[0], guid_.Data4[1], guid_.Data4[2],
                            guid_.Data4[3], guid_.Data4[4], guid_.Data4[5],
                            guid_.Data4[6], guid_.Data4[7]);

  return result;
}

ObjectId::operator StringView() const {
  return StringView{static_cast<String>(*this)};
}

auto ObjectId::IsNull() const noexcept -> bool {
  return GuidHelper::Equals(guid_, GuidHelper::Empty());
}

auto operator==(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return GuidHelper::Equals(lhs.guid_, rhs.guid_);
}

auto operator!=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return !GuidHelper::Equals(lhs.guid_, rhs.guid_);
}

auto operator<(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return static_cast<StringView>(lhs).compare(rhs) < 0;
}

auto operator<=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return static_cast<StringView>(lhs).compare(rhs) <= 0;
}

auto operator>(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return static_cast<StringView>(lhs).compare(rhs) > 0;
}

auto operator>=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return static_cast<StringView>(lhs).compare(rhs) >= 0;
}
}  // namespace afengine::foundation::internal
