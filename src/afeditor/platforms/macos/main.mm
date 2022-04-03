#include <afeditor/platforms/macos/main.h>
#include <afengine/application/Application.h>

using afengine::Application;

int main(int argc, char const *argv[]) {
  auto app = Application::Instance();

  /* code */
  return NSApplicationMain(argc, argv);
}
