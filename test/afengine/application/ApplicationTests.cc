#include <afengine/application/ApplicationTests.h>

namespace afengine {
void ApplicationTests::SetUp() {
  app = Application::Instance();
}

void ApplicationTests::TearDown() {}

TEST_F(ApplicationTests, instance) {
  ASSERT_NE(app, nullptr);
  ASSERT_EQ(app, Application::Instance());
}
}  // namespace afengine
