#ifndef AFENGINE_FOUNDATION_OBJECTID_TESTS_H
#define AFENGINE_FOUNDATION_OBJECTID_TESTS_H

#include <afengine/foundation/concepts.h>
#include <afengine/foundation/object/id/ObjectId.h>
#include <gtest/gtest.h>

#include <memory>

namespace afengine::foundation {

template <FactoryOf<ObjectId> Factory>
class ObjectIdTests : public testing::Test {
  public:
    auto Value() -> const ObjectId* {
      if (value_ == nullptr) {
        value_ = CreateValue();
      }

      return value_.get();
    }

  private:
    auto CreateValue() const requires StaticFactoryOf<Factory, ObjectId> {
      return std::make_unique<ObjectId>(Factory::Create());
    }

    auto CreateValue() const requires InvocableFactoryOf<Factory, ObjectId> {
      Factory factory{};
      return std::make_unique<ObjectId>(factory());
    }

    auto CreateValue() const requires InstancedFactoryOf<Factory, ObjectId> {
      Factory factory{};
      return std::make_unique<ObjectId>(factory.Create());
    }

    std::unique_ptr<ObjectId> value_;
};

}  // namespace afengine::foundation

#endif
