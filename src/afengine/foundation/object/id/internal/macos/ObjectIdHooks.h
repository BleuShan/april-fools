#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H

#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/internal/BasicObjectId.h>
#include <afengine/foundation/types/string.h>

#include <array>

namespace afengine::foundation::internal {

struct AFENGINE_EXPORT ObjectIdHooks {
    using ValueTypeInfo = TypeInfo<std::array<uint8_t, kObjectIdValueMaxSize>>;
    static auto Parse(StringView value) -> typename ValueTypeInfo::value_type;
    static auto Generate() -> typename ValueTypeInfo::value_type;
    static bool IsNull(typename ValueTypeInfo::const_reference value) noexcept;
    static auto ToString(typename ValueTypeInfo::const_reference value)
        -> String;
};
}  // namespace afengine::foundation::internal

#endif
