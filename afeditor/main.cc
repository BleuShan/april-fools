#include <afengine/afengine.h>
#include <folly/Singleton.h>

using afengine::runtime::Runtime;

#if WIN32 && UNICODE
auto APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                       LPWSTR lpCmdLine, int nShowCmd) -> int
#elif WIN32
auto APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      PWSTR pCmdLine, int nCmdShow) -> int
#else
auto main(int argc, char** argv) -> int
#endif
{
  auto result = Runtime::instance().start();

  return result;
}
