#ifndef AFENGINE_FOUNDATION_OBJECTID_H
#define AFENGINE_FOUNDATION_OBJECTID_H

#include <AFEngine/export_macros.h>

#include <memory>

namespace AFEngine::Foundation {
/**
 * A unique identifier for an object
 *
 */
class AFENGINE_API ObjectId final {
 private:
  struct Implementation;
  std::unique_ptr<Implementation> implementation_;
};

}  // namespace AFEngine::Foundation

#endif
