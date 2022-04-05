//
// Created by Philippe Lafontaine on 2022-04-04.
//

#ifndef AFENGINE_FOUNDATION_TYPES_META_TYPEINFO_H
#define AFENGINE_FOUNDATION_TYPES_META_TYPEINFO_H

namespace afengine::foundation {

template <typename Type>
struct TypeInfo {
    using value_type = std::remove_all_extents_t<Type>;
    using pointer = std::add_pointer_t<value_type>;
    using const_pointer = std::add_const_t<pointer>;
    using reference = std::add_lvalue_reference_t<value_type>;
    using const_reference =
        std::add_lvalue_reference_t<std::add_const_t<value_type>>;
    using forwarding_reference = std::add_rvalue_reference_t<value_type>;
};

}  // namespace afengine::foundation

#endif  // APRILSFOOLS_REFERENCEINFO_H
