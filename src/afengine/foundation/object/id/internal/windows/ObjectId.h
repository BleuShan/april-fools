#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H

#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/internal/ObjectIdTrait.h>
#include <afengine/foundation/string.h>
#include <afengine/foundation/traits/Inherits.h>
#include <winrt/Windows.Foundation.h>

namespace afengine::foundation::internal {

class AFENGINE_EXPORT ObjectId
    : public Inherits<ObjectId, ObjectIdTrait<ObjectId, winrt::guid>> {
  public:
    using Constructors::Inherits;

    explicit operator String() const;

    [[nodiscard]] auto IsNull() const noexcept -> bool override;
};

}  // namespace afengine::foundation::internal

#endif
