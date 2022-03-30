#ifndef AFENGINE_FOUNDATION_OBJECTPOOL_H
#define AFENGINE_FOUNDATION_OBJECTPOOL_H

#include <absl/container/btree_map.h>
#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/ObjectId.h>
#include <afengine/foundation/types.h>

namespace afengine::foundation {

/**
 * A collection of
 *
 */
class AFENGINE_EXPORT ObjectPool final {
 private:
  absl::btree_map<ObjectId, size_t> index_;
};

}  // namespace afengine::foundation

#endif
