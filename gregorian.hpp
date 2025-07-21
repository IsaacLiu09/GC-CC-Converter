#ifndef GC_CC_CONVERTER_GREGORIAN_HPP_
#define GC_CC_CONVERTER_GREGORIAN_HPP_

#include <array>

namespace gc_cc_converter {
    constexpr bool is_leap_year(const int year) noexcept {
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    }

    constexpr int gregorian_day_distant(const int year, const int month1, const int date1, const int month2, const int date2) {
        if (month1 > month2 || (month1 == month2 && date1 > date2))
            return -1;
        if (month1 == month2)
            return date2 - date1;
        std::array<int, 13> month_day{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        month_day[2] += is_leap_year(year);
        int result = month_day[month1] - date1;
        for (int i = month1 + 1; i < month2; ++i)
            result += month_day[i];
        result += date2;
        return result;
    };
}

#endif