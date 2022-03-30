#ifndef AFENGINE_FOUNDATION_OBJECTID_H
#define AFENGINE_FOUNDATION_OBJECTID_H

#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/detail/ObjectId.h>
#include <afengine/foundation/string.h>

#include <utility>

namespace afengine::foundation {
/**
 * A unique identifier for an object
 *
 */
class AFENGINE_EXPORT ObjectId final : public detail::ObjectId {
 public:
  template <typename... Args>
  ObjectId(Args&&... args) : detail::ObjectId{std::forward<Args>(args)...} {};
};

}  // namespace afengine::foundation

#endif
