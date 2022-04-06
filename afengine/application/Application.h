#ifndef AFENGINE_APPLICATION_H
#define AFENGINE_APPLICATION_H

#include <functional>
#include <memory>

#include "../foundation/object/Object.h"
#include "../macros/macros.h"

namespace afengine {
class AFENGINE_EXPORT Application final : public foundation::Object {
  public:
    /**
     * Alias for the shared pointer type
     */
    using SharedPtr = std::shared_ptr<Application>;
    /**
     * Alias for the weak pointer type
     */
    using WeakPtr = std::weak_ptr<Application>;

    auto operator=(const Application& other) -> Application& { return *this; }

    static auto Instance() -> SharedPtr;

    AFENGINE_NO_EXPORT static auto Create() -> Application*;
    AFENGINE_NO_EXPORT static auto Teardown(Application* instance) -> void;

  private:
    explicit Application(const foundation::ObjectId& id)
        : foundation::Object{std::forward<decltype(id)>(id)} {}
    bool running_ = false;
};

}  // namespace afengine

#endif
