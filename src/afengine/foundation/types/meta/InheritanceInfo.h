#ifndef AFENGINE_FOUNDATION_TYPES_META_INHERITANCEINFO_H
#define AFENGINE_FOUNDATION_TYPES_META_INHERITANCEINFO_H

#include <afengine/foundation/types/concepts/concepts.h>

namespace afengine::foundation {

template <ClassLike Derived, ClassLike Base>
requires std::derived_from<Derived, Base>
struct InheritanceInfo {
    using Self = Derived;
    using Super = Base;
};

}  // namespace afengine::foundation

#endif  // AFENGINE_FOUNDATION_TYPES_META_INHERITANCEINFO_H
