#ifndef GC_CC_CONVERTER_DATA_READER_HPP_
#define GC_CC_CONVERTER_DATA_READER_HPP_

#include "gan_zhi.hpp"
#include "data.hpp"

#include "bytell_hash_map.hpp"

#include <cctype>
#include <utility>
#include <memory>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>

namespace gc_cc_converter {
    using namespace std::literals;

    constexpr Month generate_month_data(std::string_view s) {
        const bool is_run = s[0] - '0';
        const int ordinal = (std::isdigit(s[1])) ? s[1] - '0' : s[1] - 'A' + 10;
        s.remove_prefix(3);
        int day_cnt = 0;
        while (!s.empty()) {
            day_cnt *= 10;
            day_cnt += s[0] - '0';
            s.remove_prefix(1);
        }
        return Month(is_run, ordinal, day_cnt);
    }
    constexpr GanZhi generate_gz(const std::string_view &s) {
        const int tg = s[0] - '0';
        const int dz = std::isdigit(s[1]) ? s[1] - '0' : s[1] - 'A' + 10;
        return GanZhi(tg, dz);
    }
    Year generate_year_data(std::istream &is) {
        std::vector<Month> months;

        std::string era_name; int ordinal;
        std::string year_gz_code, first_day_gz_code;
        int first_day_month, first_day_date;
        std::string month_info;

        is >> year_gz_code;
        is >> ordinal >> era_name;
        is >> first_day_gz_code;
        is >> first_day_month >> first_day_date;
        while (std::isspace(is.peek())) is.ignore();
        while (std::getline(is, month_info))
            months.push_back(generate_month_data(month_info));

        return Year(std::move(era_name), ordinal, std::move(months), generate_gz(year_gz_code), generate_gz(first_day_gz_code), first_day_month, first_day_date);
    }

    class YearList {
        std::string year_data_src;
        ska::bytell_hash_map<int, Year> year_data;
    public:
        YearList() : year_data_src("./data/default"s) {}
        YearList(const std::string_view &year_data_src) : year_data_src(year_data_src) {}
        const Year &get_year_data(const int ordinal) {
            if (year_data.count(ordinal) == 0) {
                std::ifstream year_data_file(this->year_data_src + "/"s + std::to_string(ordinal) + ".txt"s);
                if (!year_data_file)
                    throw std::runtime_error(std::format("无法找到年份数据：{:s}", this->year_data_src + "/"s + std::to_string(ordinal) + ".txt"s));
                year_data.emplace(ordinal, generate_year_data(year_data_file));
            }
            return year_data[ordinal];
        }
        void clear_buffer() {
            this->year_data.clear();
        }
        void set_year_data_src(const std::string_view &src) {
            this->year_data_src = src;
            this->clear_buffer();
        }
    };
}

#endif