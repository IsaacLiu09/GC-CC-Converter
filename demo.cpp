#include "converter.hpp"

#include <iostream>

int main() {
    using namespace gc_cc_converter;
    int year, month, date;
    while (std::cin >> year >> month >> date) {
        try {
            std::cout << get_chinese_date(year, month, date).get_name() << std::endl;
        } catch (const std::runtime_error &re) {
            std::clog << re.what() << std::endl;
        }
    }
    return 0;
}