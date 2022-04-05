#ifndef AFENGINE_FOUNDATION_OBJECTID_H
#define AFENGINE_FOUNDATION_OBJECTID_H

#include <afengine/export-macros.h>
#include <afengine/foundation/object/id/internal/internal.h>
#include <afengine/foundation/types/string.h>

namespace afengine::foundation {
/**
 * A unique identifier for an object
 *
 */
using ObjectId = internal::BasicObjectId<internal::ObjectIdHooks::ValueTypeInfo,
                                         internal::ObjectIdHooks>;

}  // namespace afengine::foundation

#endif
