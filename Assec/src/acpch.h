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

#include "log/Logger.h"
#include "event/Event.h"
#include "event/WindowEvents.h"
#include "event/KeyEvents.h"
#include "event/MouseEvents.h"
#include "graphics/WindowManager.h"
#include "event/EngineEvents.h"

#include "layers/LayerStack.h"
#include "layers/Layer.h"
#include "layers/gameobjects/GameObject.h"
#include "layers/gameobjects/components/Component.h"

#include "graphics/Buffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/Camera.h"
#include "graphics/renderer/Material.h"
#include "graphics/renderer/Renderable.h"
#include "graphics/renderer/Renderer.h"
#include "graphics/renderer/Mesh.h"

#include "core/Core.h"
#include "core/Config.h"

#ifdef AC_PLATFORM_WINDOWS
#include <Windows.h>
#endif
