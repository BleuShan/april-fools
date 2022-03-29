#include <afengine/application/ApplicationTests.h>

namespace afengine {
void ApplicationTests::SetUp() {
  app = Application::instance();
}

void ApplicationTests::TearDown() {}

TEST_F(ApplicationTests, instance) {
  ASSERT_NE(app, nullptr);
  ASSERT_EQ(app, Application::instance());
}
}  // namespace afengine
