#include <AFEngine/Foundation/ObjectId/ObjectId.h>

#include <winrt/windows.foundation.h>

using AFEngine::Foundation::ObjectId;
using winrt::Windows::Foundation::GuidHelper;

struct ObjectId::Implementation {
  Implementation() : data{GuidHelper::CreateNewGuid()} {}
  winrt::guid data;
};
