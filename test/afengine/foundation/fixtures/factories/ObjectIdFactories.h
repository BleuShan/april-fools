#ifndef AFENGINE_FOUNDATION_FIXTURES_OBJECTIDFACTORIES_H
#define AFENGINE_FOUNDATION_FIXTURES_OBJECTIDFACTORIES_H

#include <gtest/gtest.h>

#include "afengine/foundation/object/id/ObjectId.h"
#include "afengine/foundation/traits/traits.h"

namespace afengine::foundation::fixtures::factories {
class ObjectIdTestFactory : public ConstEnabledFactory<ObjectId> {
  public:
#if WIN32 && UNICODE
    static constexpr StringView kStringViewValue{
        L"ce737914-d2c3-4ce6-951f-8c931161461d"};
    static constexpr StringView kShortStringViewValue{
        L"ce737914d2c34ce6951f8c931161461d"};
#else
    static constexpr StringView kStringViewValue{
        "ce737914-d2c3-4ce6-951f-8c931161461d"};
    static constexpr StringView kShortStringViewValue{
        "ce737914d2c34ce6951f8c931161461d"};
#endif
};

class DefaultObjectIdConstructor : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = void;
    auto Create() const -> ObjectId override { return ObjectId::Generate(); }
};

class ObjectIdStringConstructor : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = String;
    auto Create() const -> ObjectId override {
      return ObjectId::Parse(static_cast<String>(kStringViewValue));
    }
};

class ObjectIdStringViewConstructor : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = StringView;
    auto Create() const -> ObjectId override {
      return ObjectId::Parse(static_cast<StringView>(kStringViewValue));
    }
};

class ObjectIdShortStringConstructor : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = StringView;
    auto Create() const -> ObjectId override {
      return ObjectId::Parse(static_cast<String>(kStringViewValue));
    }
};

class ObjectIdShortStringViewConstructor : public ObjectIdTestFactory {
  public:
    using ParameterType [[maybe_unused]] = StringView;
    auto Create() const -> ObjectId override {
      return ObjectId::Parse(kShortStringViewValue);
    }
};

using ObjectIdFactories =
    testing::Types<DefaultObjectIdConstructor, ObjectIdStringConstructor,
                   ObjectIdStringViewConstructor,
                   ObjectIdShortStringConstructor,
                   ObjectIdShortStringViewConstructor>;

}  // namespace afengine::foundation::fixtures::factories

#endif
