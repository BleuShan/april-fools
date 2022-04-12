#ifndef AFENGINE_FOUNDATION_OBJECTID_TESTS_H
#define AFENGINE_FOUNDATION_OBJECTID_TESTS_H

#include <gtest/gtest.h>

#include <memory>

#include "afengine/foundation/object/object.h"

namespace afengine::foundation {

class ObjectIdTests : public testing::TestWithParam<std::optional<StringView>> {
  public:
    static auto TearDownTestSuite() -> void {
      if (value_ != nullptr) {
        value_ = nullptr;
      }
      previousParam_ = nullopt;
    }

  protected:
    static auto parseOrGenerate() -> const ObjectId& {
      auto param = GetParam();
      if (value_ == nullptr || param != previousParam_) {
        value_ = std::make_unique<ObjectId>(std::forward<ObjectId>(
            param.has_value() ? ObjectId::parse(param.value())
                              : ObjectId::generate()));
        previousParam_ = param;
      }

      return *value_;
    }

    static auto value() -> std::optional<ObjectId> {
      if (value_ == nullptr) {
        return nullopt;
      }

      return *value_;
    }

  private:
    static ParamType previousParam_;
    static std::unique_ptr<ObjectId> value_;
};

}  // namespace afengine::foundation

#endif
