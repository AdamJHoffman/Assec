#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "log/Logger.h"
#include "event/Event.h"
#include "event/WindowEvents.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"
#include "graphics/WindowManager.h"
#include "event/EngineEvents.h"

#ifdef AC_PLATFORM_WINDOWS
#include <Windows.h>
#endif
