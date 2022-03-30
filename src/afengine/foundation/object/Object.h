#ifndef AFENGINE_FOUNDATION_OBJECT_H
#define AFENGINE_FOUNDATION_OBJECT_H

#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/ObjectId.h>

namespace afengine::foundation {

/**
 * The common class for all objects.
 */
class AFENGINE_EXPORT Object {
 public:
  auto id() const -> ObjectId { return id_; }

 protected:
  Object() = default;

  ObjectId id_;
};

}  // namespace afengine::foundation

#endif
