#pragma once

// Windows specific Includes
#ifdef IRADPLATFORM_WINDOWS
//#include <Windows.h>
#endif

#include <stdint.h>

// STL Includes
#include <iostream>
#include <memory>
#include <functional>
#include <fstream>

// STL Datastructure & Algorithms
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>

// Vendors
#include <imgui.h>
#include <glm/glm.hpp>

#include "IRadiance/Framework/Base.h"
#include "IRadiance/Framework/Core/Logger.h"
#include "IRadiance/Framework/Core/Time.h"
#include "IRadiance/Framework/Core/Input.h"
#include "IRadiance/Framework/Core/KeyCodes.h"
#include "IRadiance/Framework/Core/MouseButtonCodes.h"
#include "IRadiance/Framework/Core/Locator.h"
#include "IRadiance/Framework/Utility/Utility.h"
