﻿#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>

#include <string>
#include <array>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "core/Base.h"
#include "util/Profiler.h"
#include "util/misc.h"
#include "log/Logger.h"

#ifdef AC_PLATFORM_WINDOWS
#define NOMINMAX
#include <Windows.h>
#endif // AC_PLATFORM_WINDOWS
