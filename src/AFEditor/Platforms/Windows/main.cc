#include <Windows.h>


#ifdef UNICODE
auto WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) -> int {
#else
auto WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) -> int {
#endif  // UNICODE

  return 0;
}