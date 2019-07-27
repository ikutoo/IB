#pragma once
#include <string>
#include "engine/common.h"
#include "input.h"

const int GRAPH_SIZE_X = 1920;
const int GRAPH_SIZE_Y = 1080;

const int BORDER_L = 500;
const int BORDER_R = GRAPH_SIZE_X - BORDER_L;
const int BORDER_U = 0;
const int BORDER_D = GRAPH_SIZE_Y;
const int BORDER_W = BORDER_R - BORDER_L;
const int BORDER_H = BORDER_D - BORDER_U;

const std::string DATA_PATH = "../../data/";