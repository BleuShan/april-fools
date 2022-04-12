#pragma ide diagnostic ignored "cppcoreguidelines-owning-memory"
#pragma ide diagnostic ignored "modernize-use-trailing-return-type"
#pragma ide diagnostic ignored "cppcoreguidelines-special-member-functions"
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-goto"
#include "ObjectIdTests.h"

namespace afengine::foundation {

#if WIN32 && UNICODE
static constexpr StringView kStringViewValue{
    L"CE737914-D2C3-4CE6-951F-8C931161461D"};
static constexpr StringView kShortStringViewValue{
    L"CE737914D2C34CE6951F8C931161461D"};
#else
static constexpr StringView kStringViewValue{
    "CE737914-D2C3-4CE6-951F-8C931161461D"};
static constexpr StringView kShortStringViewValue{
    "CE737914D2C34CE6951F8C931161461D"};
#endif

std::unique_ptr<ObjectId> ObjectIdTests::value_{nullptr};
ObjectIdTests::ParamType ObjectIdTests::previousParam_{nullopt};

TEST_P(ObjectIdTests, generate) {
  ASSERT_NO_THROW({ parseOrGenerate(); })
      << "Should not throw on value creation";
  ASSERT_TRUE(value().has_value()) << "Should not be null.";
  ASSERT_FALSE(value()->isNull()) << "Should not be null uuid";
}

TEST_P(ObjectIdTests, toString) {
  ASSERT_NO_THROW({ parseOrGenerate(); })
      << "Should not throw on value creation";

  const auto stringValue = value()->toString();
  ASSERT_FALSE(isEmptyOrBlank(stringValue))
      << "Should return a non empty string.";

  if (GetParam().has_value()) {
    const String expected{kStringViewValue};
    ASSERT_EQ(stringValue, expected) << "Should have the same value.";
  }
}

INSTANTIATE_TEST_SUITE_P(ObjectId, ObjectIdTests,
                         testing::Values(nullopt, kStringViewValue,
                                         kShortStringViewValue));
}  // namespace afengine::foundation
