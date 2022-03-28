#ifndef AFENGINE_FOUNDATION_OBJECTID_H
#define AFENGINE_FOUNDATION_OBJECTID_H

#include <afengine/export_macros.h>

#include <memory>

namespace afengine::foundation {
/**
 * A unique identifier for an object
 *
 */
class AFENGINE_API ObjectId final {
 private:
  struct Implementation;
  std::unique_ptr<Implementation> implementation_;
};

}  // namespace afengine::foundation

#endif
