#ifndef AFENGINE_FOUNDATION_DETAIL_OBJECTID_IMPL_H
#define AFENGINE_FOUNDATION_DETAIL_OBJECTID_IMPL_H

#include <absl/types/optional.h>
#include <afengine/export-macros.h>
#include <afengine/foundation/string.h>
#include <uuid/uuid.h>

namespace afengine::foundation::detail {

class AFENGINE_EXPORT ObjectId {
 public:
  auto isNull() const -> bool;
  operator std::string();
  operator std::string_view();
  auto operator=(const ObjectId& source) -> ObjectId&;
  auto operator==(const ObjectId& other) const -> bool;
  auto operator!=(const ObjectId& other) const -> bool;

 protected:
  ObjectId();
  ObjectId(const ObjectId& source);
  ObjectId(const std::string_view data);

  uuid_t data_{0};
  uuid_string_t stringData_ = "";
};
}  // namespace afengine::foundation::detail

#endif
