#pragma once

#ifdef XENO_BUILD_DLL 
#define XENO_API __declspec(dllexport)  
#else
#define XENO_API __declspec(dllimport)  
#endif

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#ifdef XN_DEBUG
#define XN_DEBUGBREAK() __debugbreak()
#define XN_ENABLE_ASSERTS
#else
#define XN_DEBUGBREAK()
#endif

#define XN_EXPAND_MACRO(x) x
#define XN_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)