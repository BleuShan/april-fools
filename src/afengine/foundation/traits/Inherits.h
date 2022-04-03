#ifndef AFENGINE_TRAITS_EXTENDS_H
#define AFENGINE_TRAITS_EXTENDS_H

#include <afengine/foundation/concepts.h>

namespace afengine::foundation {

template <typename SelfT, typename BaseT>
struct Inherits : public BaseT {
    using Self = SelfT;
    using Base = BaseT;
    using Constructors = Inherits<Self, BaseT>;

    using Base::Base;
};

}  // namespace afengine::foundation

#endif  // AFENGINE_TRAITS_EXTENDS_H
