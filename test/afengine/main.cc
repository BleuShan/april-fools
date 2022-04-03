#include <gtest/gtest.h>

class ThrowListener : public testing::EmptyTestEventListener {
    void OnTestPartResult(const testing::TestPartResult& result) override {
      if (result.type() == testing::TestPartResult::kFatalFailure) {
        throw testing::AssertionException(result);
      }
    }
};

#if WIN32 && UNICODE
auto wmain(int argc, wchar_t** argv) -> int {
#else
auto main(int argc, char** argv) -> int {
#endif
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new ThrowListener);
  return RUN_ALL_TESTS();
}
