#ifndef AFEENGINE_FOUNDATION_INTERNAL_OBJECTID_H
#define AFEENGINE_FOUNDATION_INTERNAL_OBJECTID_H

#include <afengine/export-macros.h>
#include <afengine/foundation/types.h>
#include <algorithm>
#include <array>
#include <numeric>

namespace afengine::foundation::internal {

constexpr size_t kObjectIdValueMaxSize = 16UL * sizeof(byte);
constexpr auto kUuidStringSegmentLengths =
    std::array<size_t, 5>{8, 4, 4, 4, 12};

constexpr auto kShortUuidStringLen = std::accumulate(
    kUuidStringSegmentLengths.begin(), kUuidStringSegmentLengths.end(), 0ULL);
constexpr auto kShortUuidStringSize = kShortUuidStringLen + 1;

template <typename Self, typename ValueTypeT>
class ObjectIdTrait {
  public:
    using ValueType = ValueTypeT;

    AFENGINE_EXPORT friend auto operator==(const Self& lhs, const Self& rhs)
        -> bool;
    AFENGINE_EXPORT friend auto operator!=(const Self& lhs, const Self& rhs)
        -> bool;
    AFENGINE_EXPORT friend auto operator<(const Self& lhs, const Self& rhs)
        -> bool;
    AFENGINE_EXPORT friend auto operator<=(const Self& lhs, const Self& rhs)
        -> bool;
    AFENGINE_EXPORT friend auto operator>(const Self& lhs, const Self& rhs)
        -> bool;
    AFENGINE_EXPORT friend auto operator>=(const Self& lhs, const Self& rhs)
        -> bool;

    ObjectIdTrait(const ObjectIdTrait& source) noexcept
        : value_{source.value_} {};
    ObjectIdTrait(ObjectIdTrait&& source) noexcept
        : value_{std::move(source.value_)} {};
    virtual ~ObjectIdTrait() = default;

    auto operator=(const ObjectIdTrait& source) -> ObjectIdTrait& = default;
    auto operator=(ObjectIdTrait&& source) noexcept -> ObjectIdTrait& = default;

    [[maybe_unused, nodiscard]] virtual auto IsNull() const noexcept
        -> bool = 0;

  protected:
    explicit ObjectIdTrait(const ValueType& value) noexcept : value_{value} {};
    explicit ObjectIdTrait(ValueType&& value) noexcept : value_{value} {};
    auto Value() const noexcept -> const ValueType& { return value_; }

  private:
    ValueType value_;
    static_assert(!std::is_reference_v<ValueType>,
                  "ValueType must not be a reference type.");
    static_assert(!std::is_pointer_v<ValueType>,
                  "ValueType must not be a pointer type.");
    static_assert(sizeof(value_) <= kObjectIdValueMaxSize,
                  "Cannot be bigger than a UUID (16 bytes).");
};

}  // namespace afengine::foundation::internal

#endif  // AFEENGINE_FOUNDATION_INTERNAL_OBJECTID_H
