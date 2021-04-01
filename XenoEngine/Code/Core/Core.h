#pragma once

#ifdef XENO_BUILD_DLL 
#define XENO_API __declspec(dllexport)  
#else
#define XENO_API __declspec(dllimport)  
#endif