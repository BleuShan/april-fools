#include <afengine/foundation/object/id/internal/windows/ObjectId.h>

using afengine::foundation::internal::ObjectId;
using winrt::Windows::Foundation::GuidHelper;

ObjectId::ObjectId() : data_{GuidHelper::CreateNewGuid()} {}
