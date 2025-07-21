#ifndef GC_CC_CONVERTER_CONVERTER_HPP_
#define GC_CC_CONVERTER_CONVERTER_HPP_

#include "data_reader.hpp"
#include "gregorian.hpp"

namespace gc_cc_converter {
    YearList year_list;

    const Date get_chinese_date(const int year, const int month, const int date) {
        const Year &year_data = year_list.get_year_data(year);
        const int day_distant = gregorian_day_distant(year, year_data.first_day_month, year_data.first_day_date, month, date);
        if (day_distant == -1) {
            const Year &year_data = year_list.get_year_data(year - 1);
            const int day_distant = 
                gregorian_day_distant(year - 1, year_data.first_day_month, year_data.first_day_date, 12, 31) +
                gregorian_day_distant(year, 1, 1, month, date) + 1;
            return year_data.get_nth_date(day_distant);
        }
        return year_data.get_nth_date(day_distant);
    }
}

#endif
