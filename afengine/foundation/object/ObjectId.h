#ifndef AFENGINE_FOUNDATION_OBJECTID_H
#define AFENGINE_FOUNDATION_OBJECTID_H

#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"
#include "internal/internal.h"

namespace afengine::foundation {
/**
 * A unique identifier for an object
 *
 */
using ObjectId = internal::BasicObjectId<internal::ObjectIdHooks::ValueTypeInfo,
                                         internal::ObjectIdHooks>;

}  // namespace afengine::foundation

#endif
