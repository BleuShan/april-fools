#ifndef AFENGINE_APPLICATION_TESTS_H
#define AFENGINE_APPLICATION_TESTS_H

#include <afengine/application/Application.h>
#include <gtest/gtest.h>

namespace afengine {
class ApplicationTests : public testing::Test {
 protected:
  auto SetUp() -> void override;
  auto TearDown() -> void override;

  Application::SharedPtr app = nullptr;
};

}  // namespace afengine
#endif
