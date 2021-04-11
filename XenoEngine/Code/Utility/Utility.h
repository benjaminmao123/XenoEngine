#pragma once

#include "Core/Core.h"

#include <string>
#include <date/date.h>

namespace Xeno::Utility
{
    XENO_API inline std::string GetDateTime()
    {
        return date::format("%m-%d-%Y_%H:%M", std::chrono::system_clock::now());
    }
}
