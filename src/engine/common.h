#pragma once
#include <string>
#include "math.h"

#define SINGLETION(T) static T* getInstance() { static T Instance; return &Instance; } \
    T(const T&) = delete;			\
    T& operator=(const T&) = delete;

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr;}

#define CHECK_RESULT(call) if (0 != call) _ASSERTE(false);