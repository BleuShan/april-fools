#include <afengine/application/Application.h>

#include <folly/Singleton.h>

using afengine::Application;
using folly::Singleton;

static Singleton<Application> DefaultApplication{Application::create,
                                                 Application::teardown};

Application& Application::instance() {
  return *DefaultApplication.get();
}

Application* Application::create() {
  return new Application();
}

void Application::teardown(Application* instance) {}
