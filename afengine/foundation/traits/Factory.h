#ifndef AFENGINE_FOUNDATION_TRAITS_ABSTRACT_FACTORY_H
#define AFENGINE_FOUNDATION_TRAITS_ABSTRACT_FACTORY_H

#include <stdexcept>

#include "afengine/foundation/types/types.h"

namespace afengine::foundation {

template <typename Result>
class Factory {
  public:
    using ResultTypeInfo = TypeInfo<Result>;
    using value_type = typename ResultTypeInfo::value_type;
    using result_type = Result;

    auto Create() -> result_type { return Instantiate(); }

  protected:
    virtual auto Instantiate() -> result_type = 0;
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
