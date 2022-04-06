#ifndef AFEENGINE_FOUNDATION_INTERNAL_OBJECTID_CONSTANTS_H
#define AFEENGINE_FOUNDATION_INTERNAL_OBJECTID_CONSTANTS_H

#include <algorithm>
#include <array>
#include <numeric>

#include "afengine/foundation/types/types.h"

namespace afengine::foundation::internal {

constexpr size_t kObjectIdValueMaxSize = 16UL * sizeof(byte);
constexpr auto kUuidStringSegmentLengths =
    std::array<size_t, 5>{8, 4, 4, 4, 12};

constexpr auto kShortUuidStringLen = std::accumulate(
    kUuidStringSegmentLengths.begin(), kUuidStringSegmentLengths.end(), 0ULL);
constexpr auto kShortUuidStringSize = kShortUuidStringLen + 1;

#if UNICODE
constexpr StringView kGuidFormat =
    L"{:08x}-{:04x}-{:04x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}";
constexpr auto kDashChar = L'-';
#else
constexpr StringView kGuidFormat =
    "{:08x}-{:04x}-{:04x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}";
constexpr auto kDashChar = '-';
#endif

constexpr auto kCStrSize =
    kShortUuidStringLen + kUuidStringSegmentLengths.size() - 1;
constexpr auto kCStrLen = kCStrSize - 1;

}  // namespace afengine::foundation::internal

#endif  // AFEENGINE_FOUNDATION_INTERNAL_OBJECTID_CONSTANTS_H
