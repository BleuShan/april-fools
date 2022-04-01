#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H

#include <afengine/export-macros.h>
#include <afengine/foundation/string.h>
#include <afengine/foundation/types.h>

#include <array>

namespace afengine::foundation::internal {
class AFENGINE_EXPORT ObjectId {
  public:
    AFENGINE_EXPORT friend auto operator==(const ObjectId& lhs,
                                           const ObjectId& rhs) -> bool;
    AFENGINE_EXPORT friend auto operator!=(const ObjectId& lhs,
                                           const ObjectId& rhs) -> bool;
    AFENGINE_EXPORT friend auto operator<(const ObjectId& lhs,
                                          const ObjectId& rhs) -> bool;
    AFENGINE_EXPORT friend auto operator<=(const ObjectId& lhs,
                                           const ObjectId& rhs) -> bool;
    AFENGINE_EXPORT friend auto operator>(const ObjectId& lhs,
                                          const ObjectId& rhs) -> bool;
    AFENGINE_EXPORT friend auto operator>=(const ObjectId& lhs,
                                           const ObjectId& rhs) -> bool;

    ~ObjectId();

    operator String();
    operator StringView();
    auto operator=(const ObjectId& source) -> ObjectId&;
    auto operator=(ObjectId&& source) -> ObjectId&;

    auto IsNull() const noexcept -> bool;

  protected:
    ObjectId();
    ObjectId(const ObjectId& source);
    ObjectId(ObjectId&& source) noexcept;
    explicit ObjectId(StringView value);

    auto cstr() -> const String::pointer;

  private:
    std::array<byte, 16> uuid_{};
    String::pointer cstr_{nullptr};
};
}  // namespace afengine::foundation::internal

#endif
