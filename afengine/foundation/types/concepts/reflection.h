#ifndef AFENGINE_FOUNDATION_TYPES_CONCEPTS_REFLECTION_H
#define AFENGINE_FOUNDATION_TYPES_CONCEPTS_REFLECTION_H

#include <concepts>

namespace afengine::foundation {
template <typename Type>
concept ClassOrEnum =
    std::is_class_v<Type> || std::is_union_v<Type> || std::is_enum_v<Type>;

template <typename Type>
concept ClassLike = std::is_class_v<Type>;

template <typename Type>
concept Polymorphic = std::is_polymorphic_v<Type>;

template <typename Type>
concept Abstract = std::is_abstract_v<Type>;

template <typename Type>
concept VirtuallyDestructible = std::has_virtual_destructor_v<Type>;

template <typename Type>
concept PlainObject = std::is_pod_v<Type>;

template <typename Type, typename Output, typename... Args>
concept Fn = std::same_as<Output, std::invoke_result_t<Type, Args...>>;

template <typename Type, typename Output, typename... Args>
concept CompatibleFn =
    std::convertible_to<std::invoke_result_t<Type, Args...>, Output>;

}  // namespace afengine::foundation

#endif  // AFENGINE_FOUNDATION_TYPES_CONCEPTS_KINDS_H
