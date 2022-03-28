#include <AFEngine/Application/ApplicationTests.h>

namespace AFEngine::Tests {
auto ApplicationTests::SetUp() -> void {
  app = &Application::instance();
}

auto ApplicationTests::TearDown() -> void {}

TEST_F(ApplicationTests, instance) {
  ASSERT_NE(app, nullptr);
  ASSERT_EQ(app, &Application::instance());
}
}  // namespace AFEngine::Tests