#include <afengine/application/Application.h>

#include <folly/Singleton.h>

using afengine::Application;
using folly::Singleton;

static Singleton<Application> DefaultApplication{Application::create,
                                                 Application::teardown};

auto Application::instance() -> SharedPtr {
  return DefaultApplication.try_get();
}

auto Application::create() -> Application* {
  return new Application();
}

auto Application::teardown(Application* instance) -> void {}
