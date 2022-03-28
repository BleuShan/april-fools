#include <afengine/foundation/ObjectId/ObjectId.h>

#include <winrt/windows.foundation.h>

using afengine::foundation::ObjectId;
using winrt::Windows::Foundation::GuidHelper;

struct ObjectId::Implementation {
  Implementation() : data{GuidHelper::CreateNewGuid()} {}

  winrt::guid data;
};
