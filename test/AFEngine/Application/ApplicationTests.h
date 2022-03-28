#include <AFEngine/Application/Application.h>
#include <gtest/gtest.h>

namespace AFEngine::Tests {
class ApplicationTests : public testing::Test {
 protected:
  virtual auto SetUp() -> void override;
  virtual auto TearDown() -> void override;

  Application* app = nullptr;
};

}  // namespace AFEngine::Tests