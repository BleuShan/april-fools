#ifndef AFENGINE_FOUNDATION_FIXTURES_OBJECTIDFACTORIES_H
#define AFENGINE_FOUNDATION_FIXTURES_OBJECTIDFACTORIES_H

#include <gtest/gtest.h>

#include "afengine/foundation/object/ObjectId.h"
#include "afengine/foundation/traits/traits.h"

namespace afengine::foundation::fixtures::factories {
class ObjectIdTestFactory : public ConstEnabledFactory<ObjectId> {
  public:
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
};

class GenerateObjectId : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = void;

    [[nodiscard]] auto Create() const -> ObjectId override {
      return ObjectId::Generate();
    }
};

class ParseObjectIdFromString : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = String;

    [[nodiscard]] auto Create() const -> ObjectId override {
      const String value{kStringViewValue};
      return ObjectId::Parse(value);
    }
};

class ParseObjectIdFromStringView : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = StringView;

    [[nodiscard]] auto Create() const -> ObjectId override {
      return ObjectId::Parse(kStringViewValue);
    }
};

class ParseObjectIdFromShortString : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = StringView;

    [[nodiscard]] auto Create() const -> ObjectId override {
      const String value{kShortStringViewValue};
      return ObjectId::Parse(value);
    }
};

class ParseObjectIdFromShortStringView : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = StringView;

    [[nodiscard]] auto Create() const -> ObjectId override {
      return ObjectId::Parse(kShortStringViewValue);
    }
};

using ObjectIdFactories =
    testing::Types<GenerateObjectId, ParseObjectIdFromString,
                   ParseObjectIdFromStringView, ParseObjectIdFromShortString,
                   ParseObjectIdFromShortStringView>;

}  // namespace afengine::foundation::fixtures::factories

#endif
