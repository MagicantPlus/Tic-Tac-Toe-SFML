#pragma once

#include <algorithm>

inline const int GLOBAL_VIDEO_WIDTH = 650;
inline const int GLOBAL_VIDEO_HEIGHT = 650;
inline const int gridlineShort = 10;
inline const int GRID_HEIGHT_UP_DELTA = GLOBAL_VIDEO_HEIGHT * 0.025;
inline const int GRIDSPACE_HEIGHT = std::min(GLOBAL_VIDEO_HEIGHT * 0.7 - GRID_HEIGHT_UP_DELTA, GLOBAL_VIDEO_WIDTH * 0.8);
inline const int GRIDSPACE_WIDTH = GRIDSPACE_HEIGHT;
inline const int gridlineLong = GRIDSPACE_WIDTH;
inline const int GRID_WIDTH_DELTA = (GLOBAL_VIDEO_WIDTH - GRIDSPACE_WIDTH) / 2;