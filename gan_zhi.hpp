#ifndef GC_CC_CONVERTER_GAN_ZHI_HPP_
#define GC_CC_CONVERTER_GAN_ZHI_HPP_

#include <string>

namespace gc_cc_converter {
    using namespace std::literals;
    
    struct TianGan {
        int x;
        constexpr TianGan(const int x) : x(x) {}
        constexpr std::string get_name() const {
            switch (this->x) {
                case 0: return "甲"s;
                case 1: return "乙"s;
                case 2: return "丙"s;
                case 3: return "丁"s;
                case 4: return "戊"s;
                case 5: return "己"s;
                case 6: return "庚"s;
                case 7: return "辛"s;
                case 8: return "壬"s;
                case 9: return "癸"s;
                default: return ""s;
            }
        }
        constexpr operator int() const {
            return this->x;
        }
        constexpr TianGan &operator ++() noexcept {
            ++this->x;
            this->x %= 10;
            return *this;
        }
        constexpr TianGan operator ++(int) {
            TianGan result = *this;
            ++*this;
            return result;
        }
        constexpr TianGan &operator +=(const int delta) noexcept {
            this->x += delta;
            this->x %= 10;
            return *this;
        }
    };

    struct DiZhi {
        int y;
        constexpr DiZhi(const int y) : y(y) {}
        constexpr std::string get_name() const {
            switch (this->y) {
                case 0: return "子"s;
                case 1: return "丑"s;
                case 2: return "寅"s;
                case 3: return "卯"s;
                case 4: return "辰"s;
                case 5: return "巳"s;
                case 6: return "午"s;
                case 7: return "未"s;
                case 8: return "申"s;
                case 9: return "酉"s;
                case 10: return "戌"s;
                case 11: return "亥"s;
                default: return ""s;
            }
        }
        constexpr operator int() const {
            return this->y;
        }
        constexpr DiZhi &operator ++() noexcept {
            ++this->y;
            this->y %= 12;
            return *this;
        }
        constexpr DiZhi operator ++(int) {
            DiZhi result = *this;
            ++*this;
            return result;
        }
        constexpr DiZhi &operator +=(const int delta) noexcept {
            this->y += delta;
            this->y %= 12;
            return *this;
        }
    };

    struct GanZhi {
        TianGan g;
        DiZhi z;
        constexpr GanZhi(const TianGan &g, const DiZhi &z) : g(g), z(z) {}
        constexpr std::string get_name() const {
            return this->g.get_name() + this->z.get_name();
        }
        constexpr GanZhi &operator ++() noexcept {
            ++this->g;
            ++this->z;
            return *this;
        }
        constexpr GanZhi operator ++(int) {
            GanZhi result = *this;
            ++*this;
            return result;
        }
        constexpr GanZhi &operator +=(const int delta) noexcept {
            this->g += delta;
            this->z += delta;
            return *this;
        }
        constexpr friend GanZhi operator +(GanZhi gz, const int delta) {
            return gz += delta;
        }
    };
}

#endif
