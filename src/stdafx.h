// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

extern "C"
    {
#include <orx.h>
    }

#include <spdlog/logger.h>
#include "Logger.h"

#include <imgui.h>
#include "imgui_impl_orx.h"

#include "EnumUtility.h"
#include "OrxIni.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <algorithm>
#include <functional>
#include <filesystem>


// TODO: reference additional headers your program requires here
