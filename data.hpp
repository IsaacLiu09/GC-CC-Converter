#ifndef GC_CC_CONVERTER_DATA_HPP_
#define GC_CC_CONVERTER_DATA_HPP_

#include "gan_zhi.hpp"

#include <cctype>
#include <vector>
#include <string>
#include <format>

namespace gc_cc_converter {
    using namespace std::literals;

    struct YearInfo {
        const std::string era_name;
        const int ordinal;
        const GanZhi year_gz;
        constexpr YearInfo(std::string era_name, const int ordinal, const GanZhi &year_gz) : era_name(std::move(era_name)), ordinal(ordinal), year_gz(year_gz) {}
    };

    struct MonthInfo {
        const bool is_run;
        const int ordinal;
        constexpr MonthInfo(const bool is_run, const int ordinal) : is_run(is_run), ordinal(ordinal) {}
        constexpr std::string get_name() const {
            std::string result;
            switch (this->ordinal) {
                case 1: {
                    result = "正月"s;
                    break;
                }
                case 2: {
                    result = "二月"s;
                    break;
                }
                case 3: {
                    result = "三月"s;
                    break;
                }
                case 4: {
                    result = "四月"s;
                    break;
                }
                case 5: {
                    result = "五月"s;
                    break;
                }
                case 6: {
                    result = "六月"s;
                    break;
                }
                case 7: {
                    result = "七月"s;
                    break;
                }
                case 8: {
                    result = "八月"s;
                    break;
                }
                case 9: {
                    result = "九月"s;
                    break;
                }
                case 10: {
                    result = "十月"s;
                    break;
                }
                case 11: {
                    result = "十一月"s;
                    break;
                }
                case 12: {
                    result = "十二月"s;
                    break;
                }
            }
            if (this->is_run)
                return "闰"s + result;
            return result;
        }
    };

    struct DateInfo {
        const int ordinal;
        const GanZhi day_gz;
        constexpr DateInfo(const int ordinal, const GanZhi &day_gz) : ordinal(ordinal), day_gz(day_gz) {}
        constexpr std::string get_ordinal_name() const {
            switch (this->ordinal) {
                case 1: return "初一"s;
                case 2: return "初二"s;
                case 3: return "初三"s;
                case 4: return "初四"s;
                case 5: return "初五"s;
                case 6: return "初六"s;
                case 7: return "初七"s;
                case 8: return "初八"s;
                case 9: return "初九"s;
                case 10: return "初十"s;
                case 11: return "十一"s;
                case 12: return "十二"s;
                case 13: return "十三"s;
                case 14: return "十四"s;
                case 15: return "十五"s;
                case 16: return "十六"s;
                case 17: return "十七"s;
                case 18: return "十八"s;
                case 19: return "十九"s;
                case 20: return "二十"s;
                case 21: return "二十一"s;
                case 22: return "二十二"s;
                case 23: return "二十三"s;
                case 24: return "二十四"s;
                case 25: return "二十五"s;
                case 26: return "二十六"s;
                case 27: return "二十七"s;
                case 28: return "二十八"s;
                case 29: return "二十九"s;
                case 30: return "三十"s; 
                default: return ""s;
            }
        }
    };

    struct Date {
        const YearInfo year;
        const MonthInfo month;
        const DateInfo info;
        constexpr Date(const YearInfo &year, const MonthInfo &month, const DateInfo &info) : year(year), month(month), info(info) {}
        std::string get_name() const {
            std::string year_ordinal_name;
            if (this->year.ordinal == 1) year_ordinal_name = "元"s;
            else year_ordinal_name = std::to_string(this->year.ordinal);
            return std::format("{:s}{:s}年（{:s}）\n{:s}{:s}（{:s}）", this->year.era_name, year_ordinal_name, this->year.year_gz.get_name(), this->month.get_name(), this->info.get_ordinal_name(), this->info.day_gz.get_name());
        }
    };

    constexpr YearInfo illegal_year_info(""s, -1, GanZhi(-1, -1));
    constexpr MonthInfo illegal_month_info(false, -1);
    constexpr DateInfo illegal_date_info(-1, GanZhi(-1, -1));
    constexpr Date illegal_date(illegal_year_info, illegal_month_info, illegal_date_info);

    struct Month {
        const MonthInfo info;
        const int day_cnt;
        constexpr Month(const bool is_run, const int ordinal, const int day_cnt) : info(is_run, ordinal), day_cnt(day_cnt) {}
    };

    struct Year {
        const YearInfo info;
        const std::vector<Month> months;
        const GanZhi first_day_gz;
        const int first_day_month, first_day_date;
        constexpr Year(std::string era_name, const int ordinal, std::vector<Month> months, const GanZhi &year_gz, const GanZhi &first_day_gz, const int first_day_month, const int first_day_date) : info(std::move(era_name), ordinal, year_gz), months(std::move(months)), first_day_gz(first_day_gz), first_day_month(first_day_month), first_day_date(first_day_date) {}
        constexpr Date get_nth_date(const int n) const {
            int m = n;
            for (const Month &month : this->months) {
                if (month.day_cnt > m)
                    return Date(this->info, month.info, DateInfo(m + 1, this->first_day_gz + n));
                m -= month.day_cnt;
            }
            return illegal_date;
        }
    };
}

#endif