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
    [[nodiscard]] auto id() const -> ObjectId { return id_; }

  protected:
    explicit Object(const ObjectId& id) noexcept
        : id_{std::forward<decltype(id)>(id)} {};

  private:
    ObjectId id_;
};

}  // namespace afengine::foundation

#endif
