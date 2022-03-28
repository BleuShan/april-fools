#include <gtest/gtest.h>


#if WIN32 && UNICODE
auto wmain(int argc, wchar_t** argv) -> int {
#else
auto main(int argc, char** argv) -> int {
#endif
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}