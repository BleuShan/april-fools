#include <afengine/foundation/object/id/ObjectIdTests.h>

namespace afengine::foundation {

TEST_F(ObjectIdTests, DefaultCtor) {
  ObjectId a;
  ObjectId b;
  EXPECT_NE(a, b) << "Should generate different random id.";
  EXPECT_FALSE(a.isNull()) << "Should not be null.";
  EXPECT_FALSE(b.isNull()) << "Should not be null.";
}

TEST_F(ObjectIdTests, StringCtor) {
  ObjectId a{kStringValue};
  ObjectId b{kShortStringValue};
  EXPECT_EQ(a, b) << "should parse both uuid correctly.";
  EXPECT_EQ(kStringValue, static_cast<std::string>(b))
      << "should convert to long form";
  EXPECT_FALSE(a.isNull()) << "Should not be null.";
  EXPECT_FALSE(b.isNull()) << "Should not be null.";
}

TEST_F(ObjectIdTests, StringViewCtor) {
  ObjectId a{kStringViewValue};
  ObjectId b{kShortStringViewValue};
  EXPECT_EQ(a, b) << "should parse both uuid correctly.";
  EXPECT_EQ(kStringViewValue, static_cast<std::string_view>(b))
      << "should convert to long form.";

  EXPECT_FALSE(a.isNull()) << "Should not be null.";
  EXPECT_FALSE(b.isNull()) << "Should not be null.";
}

TEST_F(ObjectIdTests, CopyCtor) {
  ObjectId a{};
  ObjectId b{a};
  EXPECT_EQ(a, b) << "Should generate copy itself.";
  EXPECT_NE(&a, &b) << "Should not be the same pointer.";
}

TEST_F(ObjectIdTests, CopyAssignment) {
  ObjectId a{};
  ObjectId b{};
  EXPECT_FALSE(a.isNull()) << "Should not be null.";
  EXPECT_FALSE(b.isNull()) << "Should not be null.";
  EXPECT_NE(a, b) << "Should generate different random ";
  b = a;
  EXPECT_EQ(a, b) << "Should generate copy itself.";
  EXPECT_NE(&a, &b) << "Should not be the same pointer.";
}
}  // namespace afengine::foundation
