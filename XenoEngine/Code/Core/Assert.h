#pragma once

#include "Core/Core.h"
#include "Core/Logger.h"

#include <filesystem>

#ifdef XN_ENABLE_ASSERTS
// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define XN_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { XN##type##ERROR(msg, __VA_ARGS__); XN_DEBUGBREAK(); } }
#define XN_INTERNAL_ASSERT_WITH_MSG(type, check, ...) XN_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define XN_INTERNAL_ASSERT_NO_MSG(type, check) XN_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", XN_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define XN_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define XN_INTERNAL_ASSERT_GET_MACRO(...) XN_EXPAND_MACRO( XN_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, XN_INTERNAL_ASSERT_WITH_MSG, XN_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define XN_ASSERT(...) XN_EXPAND_MACRO( XN_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define XN_CORE_ASSERT(...) XN_EXPAND_MACRO( XN_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define XN_ASSERT(...)
#define XN_CORE_ASSERT(...)
#endif