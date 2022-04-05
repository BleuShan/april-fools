#ifndef AFENGINE_FOUNDATION_TRAITS_ABSTRACT_FACTORY_H
#define AFENGINE_FOUNDATION_TRAITS_ABSTRACT_FACTORY_H

#include <stdexcept>

#include "afengine/foundation/types/concepts/concepts.h"

namespace afengine::foundation {

template <typename ValueType>
class Factory {
  public:
    using ValueTypeInfo = TypeInfo<ValueType>;
    using typename ValueTypeInfo::const_reference;
    using typename ValueTypeInfo::forwarding_reference;
    using typename ValueTypeInfo::reference;
    using typename ValueTypeInfo::value_type;

    [[nodiscard]] virtual auto Create() -> ValueType = 0;
    virtual ~Factory() = default;
};

template <typename OutputType>
class ConstEnabledFactory {
  public:
    using ValueType = OutputType;

    [[nodiscard]] virtual auto Create() const -> ValueType = 0;
    virtual ~ConstEnabledFactory() = default;
};

}  // namespace afengine::foundation

#endif
