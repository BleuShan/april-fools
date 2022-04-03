#include <afengine/foundation/fixtures/factories/ObjectIdFactories.h>
#include <afengine/foundation/object/id/ObjectIdTests.h>

namespace afengine::foundation {

TYPED_TEST_SUITE_P(ObjectIdTests);

TYPED_TEST_P(ObjectIdTests, Constructor) {
  const ObjectId* value{nullptr};
  ASSERT_NO_THROW({ value = this->Value(); })
      << "Should not throw on value creation";
  ASSERT_NE(value, nullptr) << "Should not be null.";
  if constexpr (std::is_same_v<typename TypeParam::ParameterType, String>) {
    ASSERT_FALSE(value->IsNull()) << "Should not be null uuid";
  }
}

TYPED_TEST_P(ObjectIdTests, StringConversion) {
  const ObjectId* value{nullptr};
  ASSERT_NO_THROW({ value = this->Value(); })
      << "Should not throw on value creation";
  ASSERT_NE(value, nullptr) << "Should not be null.";
  ASSERT_FALSE(value->IsNull()) << "Should not be null uuid";
  if (value == nullptr) return;

  auto stringValue = static_cast<String>(*value);
  ASSERT_FALSE(IsEmptyOrBlank(stringValue))
      << "Should return a non empty string.";

  if constexpr (std::is_same_v<typename TypeParam::ParameterType, String>) {
    String expected{fixtures::factories::ObjectIdTestFactory::kStringViewValue};
    ASSERT_EQ(stringValue, expected) << "Should have the same value.";
  }
}

REGISTER_TYPED_TEST_SUITE_P(ObjectIdTests, Constructor, StringConversion);

INSTANTIATE_TYPED_TEST_SUITE_P(WithObjectIdFactories, ObjectIdTests,
                               fixtures::factories::ObjectIdFactories);
}  // namespace afengine::foundation
