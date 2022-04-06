#ifndef AFENGINE_FOUNDATION_TYPES_CONCEPTS_FACTORY_H
#define AFENGINE_FOUNDATION_TYPES_CONCEPTS_FACTORY_H

#include <concepts>

#include "ClassTypes.h"

namespace afengine::foundation {

template <typename Fn, typename Output, typename... Args>
concept InvocableFactoryOf = std::invocable<Fn, Args...> &&
    requires(Fn&& fn, Args&&... args) {
  {
    std::invoke(std::forward<Fn>(fn), std::forward<Args>(args)...)
    } -> std::convertible_to<Output>;
};

template <typename Type, typename Output, typename... Args>
concept InstancedFactoryOf = ClassLike<Type> &&
    requires(Type& factory, Args&&... args) {
  {
    factory.Create(std::forward<Args>(args)...)
    } -> std::convertible_to<Output>;
} || requires(const Type& factory, Args&&... args) {
  {
    factory.Create(std::forward<Args>(args)...)
    } -> std::convertible_to<Output>;
};

template <typename Type, typename Output, typename... Args>
concept StaticFactoryOf = ClassLike<Type> && requires(Args&&... args) {
  { Type::Create(std::forward<Args>(args)...) } -> std::convertible_to<Output>;
};

template <typename Type, typename Output, typename... Args>
concept FactoryOf = StaticFactoryOf<Type, Output, Args...> ||
    InvocableFactoryOf<Type, Output, Args...> ||
    InstancedFactoryOf<Type, Output, Args...>;

}  // namespace afengine::foundation

#endif
