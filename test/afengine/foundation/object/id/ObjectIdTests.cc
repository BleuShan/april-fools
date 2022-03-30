#include <afengine/foundation/object/id/ObjectIdTests.h>

namespace afengine::foundation {

TEST_F(ObjectIdTests, DefaultCtor) {
  ObjectId id;
  ObjectId id2;
  EXPECT_NE(id, id2) << "Should generate different random id";
  EXPECT_FALSE(id.isNull()) << "Should not be null";
  EXPECT_FALSE(id2.isNull()) << "Should not be null";
}

TEST_F(ObjectIdTests, StringCtor) {
  ObjectId a{kStringValue};
  ObjectId b{kShortStringValue};
  EXPECT_EQ(a, b) << "should parse both uuid correctly";
  EXPECT_EQ(kStringValue, static_cast<std::string>(b))
      << "should convert to long form";
  EXPECT_FALSE(a.isNull()) << "Should not be null";
  EXPECT_FALSE(b.isNull()) << "Should not be null";
}

TEST_F(ObjectIdTests, StringViewCtor) {
  ObjectId a{kStringViewValue};
  ObjectId b{kShortStringViewValue};
  EXPECT_EQ(a, b) << "should parse both uuid correctly";
  EXPECT_EQ(kStringViewValue, static_cast<std::string_view>(b))
      << "should convert to long form";

  EXPECT_FALSE(a.isNull()) << "Should not be null";
  EXPECT_FALSE(b.isNull()) << "Should not be null";
}

}  // namespace afengine::foundation
