#include <afengine/application/Application.h>
#include <afeditor/platforms/macOS/main.h>

using afengine::Application;

int main(int argc, char const *argv[]) {
  auto app = Application::instance();

  /* code */
  return NSApplicationMain(argc, argv);
}
