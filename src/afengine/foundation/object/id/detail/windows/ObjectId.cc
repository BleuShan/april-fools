#include <afengine/foundation/object/id/detail/windows/ObjectId.h>

using afengine::foundation::detail::ObjectId;
using winrt::Windows::Foundation::GuidHelper;

ObjectId::ObjectId() : data_{GuidHelper::CreateNewGuid()} {}
