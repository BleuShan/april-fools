#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTID_IMPL_H

#include <afengine/export-macros.h>
#include <afengine/foundation/string.h>
#include <afengine/foundation/types.h>

#include <array>

namespace afengine::foundation::internal {
class AFENGINE_EXPORT ObjectId {
 public:
  ~ObjectId();

  operator std::string();
  operator std::string_view();
  auto operator=(const ObjectId& source) -> ObjectId&;
  auto operator=(ObjectId&& source) -> ObjectId&;
  auto operator==(const ObjectId& other) const -> bool;
  auto operator!=(const ObjectId& other) const -> bool;
  auto operator<(const ObjectId& other) const -> bool;
  auto operator<=(const ObjectId& other) const -> bool;
  auto operator>(const ObjectId& other) const -> bool;
  auto operator>=(const ObjectId& other) const -> bool;

  auto isNull() const noexcept -> bool;
  auto cstr() -> const char*;

 protected:
  ObjectId();
  ObjectId(const ObjectId& source);
  ObjectId(const std::string_view data);
  ObjectId(ObjectId&& source);

  std::array<byte, 16> uuid_{};
  char* cstr_{nullptr};
};
}  // namespace afengine::foundation::internal

#endif
