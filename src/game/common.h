#pragma once
#include <string>
#include "engine/common.h"

#define GRAPH_SIZE_X 1920
#define GRAPH_SIZE_Y 1080

const std::string RES_IMG_ROOT = "../../res/images/";
const std::string RES_SND_ROOT = "../../res/sounds/";

#define LOCATE_FILE(file) (CResourceManager::getInstance()->locateFile(file)).c_str()