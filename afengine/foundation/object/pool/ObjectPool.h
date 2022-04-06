#ifndef AFENGINE_FOUNDATION_OBJECTPOOL_H
#define AFENGINE_FOUNDATION_OBJECTPOOL_H

#include <absl/container/btree_map.h>
#include "afengine/foundation/object/id/ObjectId.h"
#include "internal/ObjectPoolAllocator.h"
#include "afengine/macros.h"

#include "../../types/types.h"

namespace afengine::foundation {

/**
 * An ObjectPool is an object database for all objects created at runtime.
 */
class AFENGINE_EXPORT ObjectPool final {
    absl::btree_map<ObjectId, size_t> index_;
};

}  // namespace afengine::foundation

#endif
