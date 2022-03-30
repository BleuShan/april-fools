#ifndef AFENGINE_FOUNDATION_OBJECTID_TESTS_H
#define AFENGINE_FOUNDATION_OBJECTID_TESTS_H

#include <afengine/foundation/object/id/objectId.h>
#include <gtest/gtest.h>

namespace afengine::foundation {
class ObjectIdTests : public testing::Test {
 protected:
  const std::string kStringValue = "9c987abd-79f9-4201-ab23-c33a0ed5ee3e"s;
  const std::string kShortStringValue = "9c987abd79f94201ab23c33a0ed5ee3e"s;
  const std::string_view kStringViewValue =
      "ce737914-d2c3-4ce6-951f-8c931161461d"sv;
  const std::string_view kShortStringViewValue =
      "ce737914d2c34ce6951f8c931161461d"sv;
};
}  // namespace afengine::foundation

#endif
