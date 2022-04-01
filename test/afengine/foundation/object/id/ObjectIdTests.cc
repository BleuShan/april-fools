#include <afengine/foundation/object/id/ObjectIdTests.h>

namespace afengine::foundation {
TEST_F(ObjectIdTests, DefaultCtor) {
  ObjectId a{};
  ObjectId b{};
  EXPECT_NE(a, b) << "Should generate different random id.";
  EXPECT_FALSE(a.IsNull()) << "Should not be null.";
  EXPECT_FALSE(b.IsNull()) << "Should not be null.";
}

TEST_F(ObjectIdTests, StringCtor) {
  EXPECT_NO_THROW(value(kStringValue)) << "Should parse the value correctly";
  EXPECT_STREQ(kStringValue.c_str(), static_cast<String>(value()).c_str())
      << "should yield the same string back";
  EXPECT_FALSE(value().IsNull()) << "Should not be null.";
}

TEST_F(ObjectIdTests, ShortStringCtor) {
  EXPECT_NO_THROW(value(kShortStringValue))
      << "Should parse the value correctly";
  EXPECT_STREQ(kStringValue.c_str(), static_cast<String>(value()).c_str())
      << "should yield the long string back";
  EXPECT_FALSE(value().IsNull()) << "Should not be null.";
}

TEST_F(ObjectIdTests, StringViewCtor) {
  EXPECT_NO_THROW(value(kStringViewValue))
      << "Should parse the value correctly";
  EXPECT_STREQ(kStringViewValue.data(), static_cast<StringView>(value()).data())
      << "should yield the same string back";
  EXPECT_FALSE(value().IsNull()) << "Should not be null.";
}

TEST_F(ObjectIdTests, ShortStringViewCtor) {
  EXPECT_NO_THROW(value(kShortStringViewValue))
      << "Should parse the value correctly";
  EXPECT_STREQ(kStringViewValue.data(), static_cast<StringView>(value()).data())
      << "should yield the long string back";
  EXPECT_FALSE(value().IsNull()) << "Should not be null.";
}

TEST_F(ObjectIdTests, CopyCtor) {
  ObjectId a{};
  auto b{a};
  EXPECT_EQ(a, b) << "Should generate copy itself.";
  EXPECT_NE(&a, &b) << "Should not be the same pointer.";
}

TEST_F(ObjectIdTests, CopyAssignment) {
  ObjectId a{};
  ObjectId b{};
  EXPECT_FALSE(a.IsNull()) << "Should not be null.";
  EXPECT_FALSE(b.IsNull()) << "Should not be null.";
  EXPECT_NE(a, b) << "Should generate different random ";
  b = a;
  EXPECT_EQ(a, b) << "Should generate copy itself.";
  EXPECT_NE(&a, &b) << "Should not be the same pointer.";
}
}  // namespace afengine::foundation
