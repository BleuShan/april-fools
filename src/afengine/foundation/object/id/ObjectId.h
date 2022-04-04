#ifndef AFENGINE_FOUNDATION_OBJECTID_H
#define AFENGINE_FOUNDATION_OBJECTID_H

#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/internal/internal.h>
#include <afengine/foundation/string.h>

namespace afengine::foundation {
/**
 * A unique identifier for an object
 *
 */
class AFENGINE_EXPORT ObjectId final
    : public Inherits<ObjectId, internal::ObjectId> {
  public:
    using Constructors::Inherits;

    static auto Parse(StringView value) -> ObjectId {
      const auto result = Base::Parse(value);
      return ObjectId{result};
    }

    static auto Generate() -> ObjectId {
      const auto result = Base::Generate();
      return ObjectId{result};
    }
};

}  // namespace afengine::foundation

#endif
