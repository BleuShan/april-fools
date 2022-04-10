#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTIDHOOKS_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTIDHOOKS_H

#include <winrt/Windows.Foundation.h>

#include "../BasicObjectId.h"
#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"

namespace afengine::foundation::internal {

struct AFENGINE_EXPORT ObjectIdHooks {
    using ValueTypeInfo = TypeInfo<winrt::guid>;
    static auto Parse(StringView value) -> ValueTypeInfo::value_type;
    static auto Generate() -> ValueTypeInfo::value_type;
    static auto IsNull(ValueTypeInfo::const_reference value) noexcept -> bool;
    static auto ToString(ValueTypeInfo::const_reference value) -> String;
};

}  // namespace afengine::foundation::internal

#endif
