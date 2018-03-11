#ifndef P3D_COMMON_TYPES_HPP
#define P3D_COMMON_TYPES_HPP

#include <irrlicht.h>
#include <sstream>
#include <stdint.h>

typedef float float32_t;

typedef double float64_t;

int64_t getPerfTimer();

int64_t getPerfTimerFrequency();

std::string printDate();

std::string printSystemTime();

std::string printLocalTime();

std::string printTimer();

#endif // P3D_COMMON_TYPES_HPP
