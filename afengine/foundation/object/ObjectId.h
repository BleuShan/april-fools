#ifndef AFEENGINE_FOUNDATION_OBJECTID_H
#define AFEENGINE_FOUNDATION_OBJECTID_H

#include "ObjectIdTraits.h"
#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"
#include "constants.h"

namespace afengine::foundation {

template <typename ValueT, typename Traits = ObjectIdTraits<ValueT>>
class BasicObjectId {
    using const_reference = typename Traits::const_reference;
    using forwarding_reference = typename Traits::forwarding_reference;
    using value_type = typename Traits::value_type;

    value_type value_{};
    static_assert(sizeof(value_) <= kObjectIdValueMaxSize,
                  "Cannot be bigger than a UUID (16 bytes).");

  protected:
    explicit BasicObjectId(const_reference value) noexcept : value_{value} {};
    explicit BasicObjectId(forwarding_reference value) noexcept
        : value_{value} {};

  public:
    friend auto operator==(const BasicObjectId& lhs, const BasicObjectId& rhs)
        -> bool;
    friend auto operator!=(const BasicObjectId& lhs, const BasicObjectId& rhs)
        -> bool;
    friend auto operator<(const BasicObjectId& lhs, const BasicObjectId& rhs)
        -> bool;
    friend auto operator<=(const BasicObjectId& lhs, const BasicObjectId& rhs)
        -> bool;
    friend auto operator>(const BasicObjectId& lhs, const BasicObjectId& rhs)
        -> bool;
    friend auto operator>=(const BasicObjectId& lhs, const BasicObjectId& rhs)
        -> bool;

    BasicObjectId() = delete;
    BasicObjectId(const BasicObjectId& source) noexcept
        : value_{source.value_} {};
    BasicObjectId(BasicObjectId&& source) noexcept
        : value_{std::move(source.value_)} {};
    ~BasicObjectId() = default;

    auto operator=(const BasicObjectId& source) -> BasicObjectId& = default;
    auto operator=(BasicObjectId&& source) noexcept -> BasicObjectId& = default;

    static auto parse(StringView value) -> BasicObjectId requires
        Fn<decltype(Traits::parse), value_type, StringView> {
      auto result = std::invoke(Traits::parse, value);
      return BasicObjectId{std::move(result)};
    }

    static auto parse(StringView value) -> BasicObjectId
        requires(std::constructible_from<value_type, StringView> &&
                 !Fn<decltype(Traits::parse), value_type, StringView>) {
      value_type result{value};
      return BasicObjectId{result};
    }

    static auto generate()
        -> BasicObjectId requires Fn<decltype(Traits::generate), value_type> {
      auto result = std::invoke(Traits::generate);
      return BasicObjectId{std::move(result)};
    }

    [[nodiscard]] auto toString() const -> String requires
        Fn<decltype(Traits::toString), String, const_reference> {
      return std::invoke(Traits::toString, value_);
    }

    [[nodiscard]] auto isNull() const noexcept -> bool requires
        std::predicate<decltype(Traits::isNull), const_reference> {
      return std::invoke(Traits::isNull, value_);
    };

    [[nodiscard]] auto isNull() const noexcept -> bool requires(
        !std::predicate<decltype(Traits::isNull), const_reference>) {
      return false;
    };
};

using ObjectId = BasicObjectId<Uuid>;

}  // namespace afengine::foundation

#endif  // AFEENGINE_FOUNDATION_INTERNAL_BASICOBJECTID_H
