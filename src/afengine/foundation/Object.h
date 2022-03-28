#ifndef AFENGINE_FOUNDATION_OBJECT_H
#define AFENGINE_FOUNDATION_OBJECT_H

#include <afengine/export_macros.h>

#include <memory>

namespace afengine::foundation {
/**
 * The common trait class for all objects.
 *
 * @tparam Derived a concrete type deriving object.
 */
template <typename Derived>
class Object {
 public:
  /**
   * Alias for the shared pointer type
   */
  using SharedPtr = std::shared_ptr<Derived>;
  /**
   * Alias for the weak pointer type
   */
  using WeakPtr = std::weak_ptr<Derived>;

 protected:
  Object() = default;
};

}  // namespace afengine::foundation

#endif
