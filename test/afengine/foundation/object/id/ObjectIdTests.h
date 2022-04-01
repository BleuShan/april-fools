#ifndef AFENGINE_FOUNDATION_OBJECTID_TESTS_H
#define AFENGINE_FOUNDATION_OBJECTID_TESTS_H

#include <afengine/foundation/object/id/ObjectId.h>
#include <gtest/gtest.h>

#include <concepts>

namespace afengine::foundation {
class ObjectIdTests : public testing::Test {
  protected:
#if WIN32 && UNICODE
    const String kStringValue{L"9c987abd-79f9-4201-ab23-c33a0ed5ee3e"};
    const String kShortStringValue{L"9c987abd79f94201ab23c33a0ed5ee3e"};
    const StringView kStringViewValue{L"ce737914-d2c3-4ce6-951f-8c931161461d"};
    const StringView kShortStringViewValue{L"ce737914d2c34ce6951f8c931161461d"};
#else
    const String kStringValue{"9c987abd-79f9-4201-ab23-c33a0ed5ee3e"};
    const String kShortStringValue{"9c987abd79f94201ab23c33a0ed5ee3e"};
    const String kStringViewValue{"ce737914-d2c3-4ce6-951f-8c931161461d"};
    const StringView kShortStringViewValue{"ce737914d2c34ce6951f8c931161461d"};
#endif

    auto TearDown() -> void override {
      if (value_ != nullptr) {
        value_ = nullptr;
      }
    }

    [[nodiscard]] auto value() const -> ObjectId& { return *value_; }

    auto value(std::convertible_to<StringView> auto&& value) -> ObjectId& {
      value_ = std::make_unique<ObjectId>(std::forward<decltype(value)>(value));
      return *value_;
    }

  private:
    std::unique_ptr<ObjectId> value_{nullptr};
};
}  // namespace afengine::foundation

#endif
