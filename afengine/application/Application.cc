#include "Application.h"

#include <folly/Singleton.h>

#include "afengine/foundation/object/Object.h"

using afengine::Application;
using afengine::foundation::ObjectId;
using folly::Singleton;

static Singleton<Application> DefaultApplication{Application::Create,
                                                 Application::Teardown};

auto Application::Instance() -> SharedPtr {
  return DefaultApplication.try_get();
}

auto Application::Create() -> Application* {
  auto id = ObjectId::Generate();
  return new Application{id};
}

auto Application::Teardown(Application* instance) -> void {}
