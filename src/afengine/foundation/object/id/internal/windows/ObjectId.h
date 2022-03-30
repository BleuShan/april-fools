#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H

#include <afengine/export-macros.h>
#include <winrt/windows.foundation.h>

namespace afengine::foundation::internal {

class AFENGINE_PUBLIC ObjectId {
 public:
  ObjectId();

 protected:
  winrt::guid data_;
};

}  // namespace afengine::foundation::internal

#endif
