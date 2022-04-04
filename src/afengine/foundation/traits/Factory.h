#ifndef AFENGINE_FOUNDATION_TRAITS_ABSTRACT_FACTORY_H
#define AFENGINE_FOUNDATION_TRAITS_ABSTRACT_FACTORY_H

#include <afengine/foundation/concepts.h>

#include <stdexcept>

namespace afengine::foundation {

template <typename OutputType>
class Factory {
  public:
    using ValueType = OutputType;

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
