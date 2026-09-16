#pragma once

#include <cstdint>
#include <bitset>
#include <cassert>

namespace engine {

using Entity = uint32_t;
constexpr Entity NULL_ENTITY = 0;

constexpr size_t MAX_COMPONENTS = 32;
using ComponentMask = std::bitset<MAX_COMPONENTS>;

inline ComponentMask get_component_mask() { return ComponentMask{}; }

template<typename... Args>
ComponentMask get_component_mask() { return ComponentMask{}; }

} // namespace engine
