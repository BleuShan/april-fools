#ifndef AFEENGINE_FOUNDATION_OBJECT_CONSTANTS_H
#define AFEENGINE_FOUNDATION_OBJECT_CONSTANTS_H

#include <algorithm>
#include <array>
#include <numeric>

#include "afengine/foundation/types/types.h"

namespace afengine::foundation {

constexpr size_t kObjectIdValueMaxSize = 16UL * sizeof(byte);
constexpr auto kUuidStringSegmentLengths =
    std::array<size_t, 5>{8, 4, 4, 4, 12};

constexpr auto kShortUuidStringLen = std::accumulate(
    kUuidStringSegmentLengths.begin(), kUuidStringSegmentLengths.end(), 0ULL);
constexpr auto kShortUuidStringSize = kShortUuidStringLen + 1;

#if UNICODE
constexpr StringView kGuidFormat =
    L"{:08X}-{:04X}-{:04X}-{:02X}{:02X}-{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}";
constexpr auto kDashChar = L'-';
#else
constexpr StringView kGuidFormat =
    "{:08X}-{:04X}-{:04X}-{:02X}{:02X}-{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}";
constexpr auto kDashChar = '-';
#endif

constexpr auto kCStrSize =
    kShortUuidStringLen + kUuidStringSegmentLengths.size();
constexpr auto kCStrLen = kCStrSize - 1;

}  // namespace afengine::foundation

#endif  // AFEENGINE_FOUNDATION_INTERNAL_OBJECTID_CONSTANTS_H
