#pragma once
#include <string>
#include "engine/common.h"

#define WIDTH 1920
#define HEIGHT 1080

const std::string RES_IMG_ROOT = "../../res/images/";
const std::string RES_SND_ROOT = "../../res/sounds/";
#define LOCATE_IMAGE(file) (RES_IMG_ROOT + file).c_str()
#define LOCATE_SOUND(file) (RES_SND_ROOT + file).c_str()