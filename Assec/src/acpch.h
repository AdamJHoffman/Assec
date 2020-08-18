#pragma once

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

#include "core/Config.h"
#include "util/Profiler.h"
#include "util/misc.h"
#include "log/Logger.h"

#include "scene/Entity.h"
#include "scene/Scene.h"
#include "scene/Components.h"

#ifdef AC_PLATFORM_WINDOWS
#include <Windows.h>
#endif
