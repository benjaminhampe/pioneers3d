#ifndef PIONEERS3D_COMMON_UTILS_HPP
#define PIONEERS3D_COMMON_UTILS_HPP

#include <pioneers3d/common/Types.hpp>

namespace pioneers3d {

    int64_t getPerfTimer();

    int64_t getPerfTimerFrequency();

    struct GregorianDate {
        int32_t year;
        int32_t month;
        int32_t day;
    };

    struct GregorianTime {
        int32_t hour;
        int32_t minute;
        int32_t second;
        int32_t microsecond;
    };

    struct JulianDays {
        float64_t jd;
    };

    std::string printDate();

    std::string printSystemTime();

    std::string printLocalTime();

    std::string printTimer();

} // end namespace pioneers3d

#endif // PIONEERS3D_COMMON_UTILS_HPP
