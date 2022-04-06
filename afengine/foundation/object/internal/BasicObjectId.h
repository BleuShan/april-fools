#ifndef AFEENGINE_FOUNDATION_INTERNAL_BASICOBJECTID_H
#define AFEENGINE_FOUNDATION_INTERNAL_BASICOBJECTID_H

#include "afengine/macros/macros.h"
#include "afengine/foundation/types/types.h"
#include "constants.h"

namespace afengine::foundation::internal {

template <typename ValueTypeInfo, typename Hooks = void>
class AFENGINE_EXPORT BasicObjectId {
  public:
    using const_reference = typename ValueTypeInfo::const_reference;
    using forwarding_reference = typename ValueTypeInfo::forwarding_reference;
    using value_type = typename ValueTypeInfo::value_type;

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

    BasicObjectId(const BasicObjectId& source) noexcept
        : value_{source.value_} {};
    BasicObjectId(BasicObjectId&& source) noexcept
        : value_{std::move(source.value_)} {};
    ~BasicObjectId() = default;

    auto operator=(const BasicObjectId& source) -> BasicObjectId& = default;
    auto operator=(BasicObjectId&& source) noexcept -> BasicObjectId& = default;

    explicit operator String() const requires
        std::regular_invocable<decltype(Hooks::ToString), const_reference> {
      return Hooks::ToString(value_);
    }

    [[nodiscard]] auto IsNull() const noexcept -> bool requires
        std::predicate<decltype(Hooks::IsNull), const_reference> {
      return Hooks::IsNull(value_);
    };

    [[nodiscard]] auto IsNull() const noexcept -> bool requires(
        !std::predicate<decltype(Hooks::IsNull), const_reference>) {
      return false;
    };

    static auto Parse(StringView value) -> BasicObjectId requires
        std::regular_invocable<decltype(Hooks::Parse), StringView> && requires {
      { Hooks::Parse(value) } -> std::same_as<value_type>;
    }
    {
      auto result = Hooks::Parse(value);
      return BasicObjectId{result};
    }

    static auto Parse(StringView value) -> BasicObjectId
        requires(std::constructible_from<value_type, StringView> &&
                 !std::regular_invocable<decltype(Hooks::Parse), StringView>) {
      value_type result{value};
      return BasicObjectId{result};
    }

    static auto Generate() -> BasicObjectId requires
        std::regular_invocable<decltype(Hooks::Generate)> && requires {
      { Hooks::Generate() } -> std::same_as<value_type>;
    }
    {
      auto result = Hooks::Generate();
      return BasicObjectId{result};
    }

  protected:
    explicit BasicObjectId(const_reference value) noexcept : value_{value} {};
    explicit BasicObjectId(forwarding_reference value) noexcept
        : value_{value} {};
    [[maybe_unused, nodiscard]] auto Value() const noexcept -> const_reference {
      return value_;
    }

  private:
    value_type value_;
    static_assert(sizeof(value_) <= kObjectIdValueMaxSize,
                  "Cannot be bigger than a UUID (16 bytes).");
};

}  // namespace afengine::foundation::internal

#endif  // AFEENGINE_FOUNDATION_INTERNAL_BASICOBJECTID_H
