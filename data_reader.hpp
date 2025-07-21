#ifndef GC_CC_CONVERTER_DATA_READER_HPP_
#define GC_CC_CONVERTER_DATA_READER_HPP_

#include "gan_zhi.hpp"
#include "data.hpp"

#include <cctype>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>

namespace gc_cc_converter {
    using namespace std::literals;

    constexpr Month generate_month_data(std::string_view s) {
        const int is_run = s[0] - '0';
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
        constexpr static int OFFSET = 2000;
        std::string year_data_src;
        std::vector<std::unique_ptr<Year>> year_data_after, year_data_before;
        std::unique_ptr<Year> &find_year_data(int ordinal) {
            ordinal -= OFFSET;
            if (ordinal < 0) {
                ordinal = ~ordinal;
                if (static_cast<int>(this->year_data_before.size()) <= ordinal)
                    this->year_data_before.resize(ordinal + 1);
                return this->year_data_before[ordinal];
            } else {
                if (static_cast<int>(this->year_data_after.size()) <= ordinal)
                    this->year_data_after.resize(ordinal + 1);
                return this->year_data_after[ordinal];
            }
        }
    public:
        YearList() : year_data_src("./data/default"s), year_data_after(100), year_data_before(100) {}
        YearList(const std::string_view &year_data_src) : year_data_src(year_data_src), year_data_after(100), year_data_before(100) {}
        const Year &get_year_data(const int ordinal) {
            auto &data_ptr = this->find_year_data(ordinal);
            if (data_ptr == nullptr) {
                std::ifstream year_data_file(this->year_data_src + "/"s + std::to_string(ordinal) + ".txt"s);
                if (!year_data_file)
                    throw std::runtime_error(std::format("无法找到年份数据：{:s}", this->year_data_src + "/"s + std::to_string(ordinal) + ".txt"s));
                data_ptr = std::make_unique<Year>(generate_year_data(year_data_file));
            }
            return *data_ptr;
        }
        void shrink_to_fit() {
            this->year_data_before.shrink_to_fit();
            this->year_data_after.shrink_to_fit();
        }
        void clear_buffer() {
            this->year_data_before.resize(100);
            this->year_data_after.resize(100);
            for (auto &data_ptr : this->year_data_before)
                data_ptr = nullptr;
            for (auto &data_ptr : this->year_data_after)
                data_ptr = nullptr;
        }
        void set_year_data_src(const std::string_view &src) {
            this->year_data_src = src;
            this->clear_buffer();
        }
    };
}

#endif