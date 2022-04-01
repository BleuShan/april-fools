#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H

#include <afengine/export-macros.h>
#include <afengine/foundation/string.h>
#include <winrt/Windows.Foundation.h>

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

    ~ObjectId() = default;
    auto operator=(const ObjectId& source) -> ObjectId& = default;
    auto operator=(ObjectId&& source) -> ObjectId& = default;

    operator String() const;
    operator StringView() const;

    [[nodiscard]] auto IsNull() const noexcept -> bool;

  protected:
    ObjectId();
    ObjectId(const ObjectId& source) = default;
    ObjectId(ObjectId&& source) noexcept = default;
    explicit ObjectId(StringView value);

  private:
    winrt::guid guid_;
};

}  // namespace afengine::foundation::internal

#endif
