#pragma once

#include "Core/Core.h"

namespace Xeno
{
	class XENO_API NonCopyable
	{
	public:
		NonCopyable(const NonCopyable& other) = delete;
		NonCopyable& operator=(const NonCopyable& other) = delete;
		
	protected:
		NonCopyable() = default;
		~NonCopyable() = default;
	};
}