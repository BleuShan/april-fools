#ifndef AFENGINE_FOUNDATION_STRING_H
#define AFENGINE_FOUNDATION_STRING_H

#include <folly/FixedString.h>

#include <string>

using namespace std::literals;

namespace afengine::foundation {
#if UNICODE && WIN32
using String = std::wstring;
using StringView = std::wstring_view;
#else
using String = std::string;
using StringView = std::string_view;
#endif

}  // namespace afengine::foundation

#endif
