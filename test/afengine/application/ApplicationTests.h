#include <afengine/application/Application.h>
#include <gtest/gtest.h>

namespace afengine {
class ApplicationTests : public testing::Test {
 protected:
  void SetUp() override;
  void TearDown() override;

  Application::SharedPtr app = nullptr;
};

}  // namespace afengine
