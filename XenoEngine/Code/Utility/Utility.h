#pragma once

#include "Core/Core.h"
#include "Core/Assert.h"

#include <string>
#include <date/date.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace Xeno::Utility
{
    XENO_API inline std::string GetDateTime()
    {
        return date::format("%m-%d-%Y_%H:%M", std::chrono::system_clock::now());
    }
}
