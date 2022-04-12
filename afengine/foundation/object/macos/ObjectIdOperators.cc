#include <uuid/uuid.h>

#include "../ObjectId.h"

namespace afengine::foundation {

auto operator==(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) == 0;
}

auto operator!=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) != 0;
}

auto operator<(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) < 0;
}

auto operator>(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) > 0;
}

auto operator<=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) <= 0;
}

auto operator>=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return uuid_compare(lhs.value_.data(), rhs.value_.data()) >= 0;
}

}  // namespace afengine::foundation
