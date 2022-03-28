#include <AFEngine/Application/Application.h>

#include <folly/Singleton.h>

using AFEngine::Application;
using folly::Singleton;

static Singleton<Application> DefaultApplication{Application::create, Application::teardown};

auto Application::instance() -> Application& {
  return *DefaultApplication.get();
}

auto Application::create() -> Application* {
  return new Application();
}

auto Application::teardown(Application* instance) -> void {}