#include <uuid/uuid.h>

#include "../ObjectId.h"

using winrt::Windows::Foundation::GuidHelper;

namespace afengine::foundation {

auto operator==(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator!=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return !GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator<(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return lhs.value_ < rhs.value_;
}

auto operator<=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return lhs.value_ < rhs.value_ || GuidHelper::Equals(lhs.value_, rhs.value_);
}

auto operator>(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return !(lhs.value_ < rhs.value_);
}

auto operator>=(const ObjectId& lhs, const ObjectId& rhs) -> bool {
  return !(lhs.value_ < rhs.value_) &&
         !GuidHelper::Equals(lhs.value_, rhs.value_);
}

}  // namespace afengine::foundation
