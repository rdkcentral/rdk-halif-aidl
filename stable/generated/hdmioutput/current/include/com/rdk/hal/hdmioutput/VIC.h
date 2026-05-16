#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class VIC : int32_t {
  VIC0_UNAVAILABLE = 0,
  VIC1_640_480_P_60_4_3 = 1,
  VIC2_720_480_P_60_4_3 = 2,
  VIC3_720_480_P_60_16_9 = 3,
  VIC4_1280_720_P_60_16_9 = 4,
  VIC5_1920_1080_I_60_16_9 = 5,
  VIC6_720_1440_480_I_60_4_3 = 6,
  VIC7_720_1440_480_I_60_16_9 = 7,
  VIC8_720_1440_240_P_60_4_3 = 8,
  VIC9_720_1440_240_P_60_16_9 = 9,
  VIC10_2880_480_I_60_4_3 = 10,
  VIC11_2880_480_I_60_16_9 = 11,
  VIC12_2880_240_P_60_4_3 = 12,
  VIC13_2880_240_P_60_16_9 = 13,
  VIC14_1440_480_P_60_4_3 = 14,
  VIC15_1440_480_P_60_16_9 = 15,
  VIC16_1920_1080_P_60_16_9 = 16,
  VIC17_720_576_P_50_4_3 = 17,
  VIC18_720_576_P_50_16_9 = 18,
  VIC19_1280_720_P_50_16_9 = 19,
  VIC20_1920_1080_I_50_16_9 = 20,
  VIC21_720_1440_576_I_50_4_3 = 21,
  VIC22_720_1440_576_I_50_16_9 = 22,
  VIC23_720_1440_288_P_50_4_3 = 23,
  VIC24_720_1440_288_P_50_16_9 = 24,
  VIC25_2880_576_I_50_4_3 = 25,
  VIC26_2880_576_I_50_16_9 = 26,
  VIC27_2880_288_P_50_4_3 = 27,
  VIC28_2880_288_P_50_16_9 = 28,
  VIC29_1440_576_P_50_4_3 = 29,
  VIC30_1440_576_P_50_16_9 = 30,
  VIC31_1920_1080_P_50_16_9 = 31,
  VIC32_1920_1080_P_24_16_9 = 32,
  VIC33_1920_1080_P_25_16_9 = 33,
  VIC34_1920_1080_P_30_16_9 = 34,
  VIC35_2880_480_P_60_4_3 = 35,
  VIC36_2880_480_P_60_16_9 = 36,
  VIC37_2880_576_P_50_4_3 = 37,
  VIC38_2880_576_P_50_16_9 = 38,
  VIC39_1920_1080_I_50_16_9 = 39,
  VIC40_1920_1080_I_100_16_9 = 40,
  VIC41_1280_720_P_100_16_9 = 41,
  VIC42_720_576_P_100_4_3 = 42,
  VIC43_720_576_P_100_16_9 = 43,
  VIC44_720_1440_576_I_100_4_3 = 44,
  VIC45_720_1440_576_I_100_16_9 = 45,
  VIC46_1920_1080_I_120_16_9 = 46,
  VIC47_1280_720_P_120_16_9 = 47,
  VIC48_720_480_P_120_4_3 = 48,
  VIC49_720_480_P_120_16_9 = 49,
  VIC50_720_1440_480_I_120_4_3 = 50,
  VIC51_720_1440_480_I_120_16_9 = 51,
  VIC52_720_576_P_200_4_3 = 52,
  VIC53_720_576_P_200_16_9 = 53,
  VIC54_720_1440_576_I_200_4_3 = 54,
  VIC55_720_1440_576_I_200_16_9 = 55,
  VIC56_720_480_P_240_4_3 = 56,
  VIC57_720_480_P_240_16_9 = 57,
  VIC58_720_1440_480_I_240_4_3 = 58,
  VIC59_720_1440_480_I_240_16_9 = 59,
  VIC60_1280_720_P_24_16_9 = 60,
  VIC61_1280_720_P_25_16_9 = 61,
  VIC62_1280_720_P_30_16_9 = 62,
  VIC63_1920_1080_P_120_16_9 = 63,
  VIC64_1920_1080_P_100_16_9 = 64,
  VIC65_1280_720_P_24_64_27 = 65,
  VIC66_1280_720_P_25_64_27 = 66,
  VIC67_1280_720_P_30_64_27 = 67,
  VIC68_1280_720_P_50_64_27 = 68,
  VIC69_1280_720_P_60_64_27 = 69,
  VIC70_1280_720_P_100_64_27 = 70,
  VIC71_1280_720_P_120_64_27 = 71,
  VIC72_1920_1080_P_24_64_27 = 72,
  VIC73_1920_1080_P_25_64_27 = 73,
  VIC74_1920_1080_P_30_64_27 = 74,
  VIC75_1920_1080_P_50_64_27 = 75,
  VIC76_1920_1080_P_60_64_27 = 76,
  VIC77_1920_1080_P_100_64_27 = 77,
  VIC78_1920_1080_P_120_64_27 = 78,
  VIC79_1680_720_P_24_64_27 = 79,
  VIC80_1680_720_P_25_64_27 = 80,
  VIC81_1680_720_P_30_64_27 = 81,
  VIC82_1680_720_P_50_64_27 = 82,
  VIC83_1680_720_P_60_64_27 = 83,
  VIC84_1680_720_P_100_64_27 = 84,
  VIC85_1680_720_P_120_64_27 = 85,
  VIC86_2560_1080_P_24_64_27 = 86,
  VIC87_2560_1080_P_25_64_27 = 87,
  VIC88_2560_1080_P_30_64_27 = 88,
  VIC89_2560_1080_P_50_64_27 = 89,
  VIC90_2560_1080_P_60_64_27 = 90,
  VIC91_2560_1080_P_100_64_27 = 91,
  VIC92_2560_1080_P_120_64_27 = 92,
  VIC93_3840_2160_P_24_16_9 = 93,
  VIC94_3840_2160_P_25_16_9 = 94,
  VIC95_3840_2160_P_30_16_9 = 95,
  VIC96_3840_2160_P_50_16_9 = 96,
  VIC97_3840_2160_P_60_16_9 = 97,
  VIC98_4096_2160_P_24_256_135 = 98,
  VIC99_4096_2160_P_25_256_135 = 99,
  VIC100_4096_2160_P_30_256_135 = 100,
  VIC101_4096_2160_P_50_256_135 = 101,
  VIC102_4096_2160_P_60_256_135 = 102,
  VIC103_3840_2160_P_24_64_27 = 103,
  VIC104_3840_2160_P_25_64_27 = 104,
  VIC105_3840_2160_P_30_64_27 = 105,
  VIC106_3840_2160_P_50_64_27 = 106,
  VIC107_3840_2160_P_60_64_27 = 107,
  VIC108_1280_720_P_48_16_9 = 108,
  VIC109_1280_720_P_48_64_27 = 109,
  VIC110_1680_720_P_48_64_27 = 110,
  VIC111_1920_1080_P_48_16_9 = 111,
  VIC112_1920_1080_P_48_64_27 = 112,
  VIC113_2560_1080_P_48_64_27 = 113,
  VIC114_3840_2160_P_48_16_9 = 114,
  VIC115_4096_2160_P_48_256_135 = 115,
  VIC116_3840_2160_P_48_64_27 = 116,
  VIC117_3840_2160_P_100_16_9 = 117,
  VIC118_3840_2160_P_120_16_9 = 118,
  VIC119_3840_2160_P_100_64_27 = 119,
  VIC120_3840_2160_P_120_64_27 = 120,
  VIC121_5120_2160_P_24_64_27 = 121,
  VIC122_5120_2160_P_25_64_27 = 122,
  VIC123_5120_2160_P_30_64_27 = 123,
  VIC124_5120_2160_P_48_64_27 = 124,
  VIC125_5120_2160_P_50_64_27 = 125,
  VIC126_5120_2160_P_60_64_27 = 126,
  VIC127_5120_2160_P_100_64_27 = 127,
  VIC193_5120_2160_P_120_64_27 = 193,
  VIC194_7680_4320_P_24_16_9 = 194,
  VIC195_7680_4320_P_25_16_9 = 195,
  VIC196_7680_4320_P_30_16_9 = 196,
  VIC197_7680_4320_P_48_16_9 = 197,
  VIC198_7680_4320_P_50_16_9 = 198,
  VIC199_7680_4320_P_60_16_9 = 199,
  VIC200_7680_4320_P_100_16_9 = 200,
  VIC201_7680_4320_P_120_16_9 = 201,
  VIC202_7680_4320_P_24_64_27 = 202,
  VIC203_7680_4320_P_25_64_27 = 203,
  VIC204_7680_4320_P_30_64_27 = 204,
  VIC205_7680_4320_P_48_64_27 = 205,
  VIC206_7680_4320_P_50_64_27 = 206,
  VIC207_7680_4320_P_60_64_27 = 207,
  VIC208_7680_4320_P_100_64_27 = 208,
  VIC209_7680_4320_P_120_64_27 = 209,
  VIC210_10240_4320_P_24_64_27 = 210,
  VIC211_10240_4320_P_25_64_27 = 211,
  VIC212_10240_4320_P_30_64_27 = 212,
  VIC213_10240_4320_P_48_64_27 = 213,
  VIC214_10240_4320_P_50_64_27 = 214,
  VIC215_10240_4320_P_60_64_27 = 215,
  VIC216_10240_4320_P_100_64_27 = 216,
  VIC217_10240_4320_P_120_64_27 = 217,
  VIC218_4096_2160_P_100_256_135 = 218,
  VIC219_4096_2160_P_120_256_135 = 219,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(VIC val) {
  switch(val) {
  case VIC::VIC0_UNAVAILABLE:
    return "VIC0_UNAVAILABLE";
  case VIC::VIC1_640_480_P_60_4_3:
    return "VIC1_640_480_P_60_4_3";
  case VIC::VIC2_720_480_P_60_4_3:
    return "VIC2_720_480_P_60_4_3";
  case VIC::VIC3_720_480_P_60_16_9:
    return "VIC3_720_480_P_60_16_9";
  case VIC::VIC4_1280_720_P_60_16_9:
    return "VIC4_1280_720_P_60_16_9";
  case VIC::VIC5_1920_1080_I_60_16_9:
    return "VIC5_1920_1080_I_60_16_9";
  case VIC::VIC6_720_1440_480_I_60_4_3:
    return "VIC6_720_1440_480_I_60_4_3";
  case VIC::VIC7_720_1440_480_I_60_16_9:
    return "VIC7_720_1440_480_I_60_16_9";
  case VIC::VIC8_720_1440_240_P_60_4_3:
    return "VIC8_720_1440_240_P_60_4_3";
  case VIC::VIC9_720_1440_240_P_60_16_9:
    return "VIC9_720_1440_240_P_60_16_9";
  case VIC::VIC10_2880_480_I_60_4_3:
    return "VIC10_2880_480_I_60_4_3";
  case VIC::VIC11_2880_480_I_60_16_9:
    return "VIC11_2880_480_I_60_16_9";
  case VIC::VIC12_2880_240_P_60_4_3:
    return "VIC12_2880_240_P_60_4_3";
  case VIC::VIC13_2880_240_P_60_16_9:
    return "VIC13_2880_240_P_60_16_9";
  case VIC::VIC14_1440_480_P_60_4_3:
    return "VIC14_1440_480_P_60_4_3";
  case VIC::VIC15_1440_480_P_60_16_9:
    return "VIC15_1440_480_P_60_16_9";
  case VIC::VIC16_1920_1080_P_60_16_9:
    return "VIC16_1920_1080_P_60_16_9";
  case VIC::VIC17_720_576_P_50_4_3:
    return "VIC17_720_576_P_50_4_3";
  case VIC::VIC18_720_576_P_50_16_9:
    return "VIC18_720_576_P_50_16_9";
  case VIC::VIC19_1280_720_P_50_16_9:
    return "VIC19_1280_720_P_50_16_9";
  case VIC::VIC20_1920_1080_I_50_16_9:
    return "VIC20_1920_1080_I_50_16_9";
  case VIC::VIC21_720_1440_576_I_50_4_3:
    return "VIC21_720_1440_576_I_50_4_3";
  case VIC::VIC22_720_1440_576_I_50_16_9:
    return "VIC22_720_1440_576_I_50_16_9";
  case VIC::VIC23_720_1440_288_P_50_4_3:
    return "VIC23_720_1440_288_P_50_4_3";
  case VIC::VIC24_720_1440_288_P_50_16_9:
    return "VIC24_720_1440_288_P_50_16_9";
  case VIC::VIC25_2880_576_I_50_4_3:
    return "VIC25_2880_576_I_50_4_3";
  case VIC::VIC26_2880_576_I_50_16_9:
    return "VIC26_2880_576_I_50_16_9";
  case VIC::VIC27_2880_288_P_50_4_3:
    return "VIC27_2880_288_P_50_4_3";
  case VIC::VIC28_2880_288_P_50_16_9:
    return "VIC28_2880_288_P_50_16_9";
  case VIC::VIC29_1440_576_P_50_4_3:
    return "VIC29_1440_576_P_50_4_3";
  case VIC::VIC30_1440_576_P_50_16_9:
    return "VIC30_1440_576_P_50_16_9";
  case VIC::VIC31_1920_1080_P_50_16_9:
    return "VIC31_1920_1080_P_50_16_9";
  case VIC::VIC32_1920_1080_P_24_16_9:
    return "VIC32_1920_1080_P_24_16_9";
  case VIC::VIC33_1920_1080_P_25_16_9:
    return "VIC33_1920_1080_P_25_16_9";
  case VIC::VIC34_1920_1080_P_30_16_9:
    return "VIC34_1920_1080_P_30_16_9";
  case VIC::VIC35_2880_480_P_60_4_3:
    return "VIC35_2880_480_P_60_4_3";
  case VIC::VIC36_2880_480_P_60_16_9:
    return "VIC36_2880_480_P_60_16_9";
  case VIC::VIC37_2880_576_P_50_4_3:
    return "VIC37_2880_576_P_50_4_3";
  case VIC::VIC38_2880_576_P_50_16_9:
    return "VIC38_2880_576_P_50_16_9";
  case VIC::VIC39_1920_1080_I_50_16_9:
    return "VIC39_1920_1080_I_50_16_9";
  case VIC::VIC40_1920_1080_I_100_16_9:
    return "VIC40_1920_1080_I_100_16_9";
  case VIC::VIC41_1280_720_P_100_16_9:
    return "VIC41_1280_720_P_100_16_9";
  case VIC::VIC42_720_576_P_100_4_3:
    return "VIC42_720_576_P_100_4_3";
  case VIC::VIC43_720_576_P_100_16_9:
    return "VIC43_720_576_P_100_16_9";
  case VIC::VIC44_720_1440_576_I_100_4_3:
    return "VIC44_720_1440_576_I_100_4_3";
  case VIC::VIC45_720_1440_576_I_100_16_9:
    return "VIC45_720_1440_576_I_100_16_9";
  case VIC::VIC46_1920_1080_I_120_16_9:
    return "VIC46_1920_1080_I_120_16_9";
  case VIC::VIC47_1280_720_P_120_16_9:
    return "VIC47_1280_720_P_120_16_9";
  case VIC::VIC48_720_480_P_120_4_3:
    return "VIC48_720_480_P_120_4_3";
  case VIC::VIC49_720_480_P_120_16_9:
    return "VIC49_720_480_P_120_16_9";
  case VIC::VIC50_720_1440_480_I_120_4_3:
    return "VIC50_720_1440_480_I_120_4_3";
  case VIC::VIC51_720_1440_480_I_120_16_9:
    return "VIC51_720_1440_480_I_120_16_9";
  case VIC::VIC52_720_576_P_200_4_3:
    return "VIC52_720_576_P_200_4_3";
  case VIC::VIC53_720_576_P_200_16_9:
    return "VIC53_720_576_P_200_16_9";
  case VIC::VIC54_720_1440_576_I_200_4_3:
    return "VIC54_720_1440_576_I_200_4_3";
  case VIC::VIC55_720_1440_576_I_200_16_9:
    return "VIC55_720_1440_576_I_200_16_9";
  case VIC::VIC56_720_480_P_240_4_3:
    return "VIC56_720_480_P_240_4_3";
  case VIC::VIC57_720_480_P_240_16_9:
    return "VIC57_720_480_P_240_16_9";
  case VIC::VIC58_720_1440_480_I_240_4_3:
    return "VIC58_720_1440_480_I_240_4_3";
  case VIC::VIC59_720_1440_480_I_240_16_9:
    return "VIC59_720_1440_480_I_240_16_9";
  case VIC::VIC60_1280_720_P_24_16_9:
    return "VIC60_1280_720_P_24_16_9";
  case VIC::VIC61_1280_720_P_25_16_9:
    return "VIC61_1280_720_P_25_16_9";
  case VIC::VIC62_1280_720_P_30_16_9:
    return "VIC62_1280_720_P_30_16_9";
  case VIC::VIC63_1920_1080_P_120_16_9:
    return "VIC63_1920_1080_P_120_16_9";
  case VIC::VIC64_1920_1080_P_100_16_9:
    return "VIC64_1920_1080_P_100_16_9";
  case VIC::VIC65_1280_720_P_24_64_27:
    return "VIC65_1280_720_P_24_64_27";
  case VIC::VIC66_1280_720_P_25_64_27:
    return "VIC66_1280_720_P_25_64_27";
  case VIC::VIC67_1280_720_P_30_64_27:
    return "VIC67_1280_720_P_30_64_27";
  case VIC::VIC68_1280_720_P_50_64_27:
    return "VIC68_1280_720_P_50_64_27";
  case VIC::VIC69_1280_720_P_60_64_27:
    return "VIC69_1280_720_P_60_64_27";
  case VIC::VIC70_1280_720_P_100_64_27:
    return "VIC70_1280_720_P_100_64_27";
  case VIC::VIC71_1280_720_P_120_64_27:
    return "VIC71_1280_720_P_120_64_27";
  case VIC::VIC72_1920_1080_P_24_64_27:
    return "VIC72_1920_1080_P_24_64_27";
  case VIC::VIC73_1920_1080_P_25_64_27:
    return "VIC73_1920_1080_P_25_64_27";
  case VIC::VIC74_1920_1080_P_30_64_27:
    return "VIC74_1920_1080_P_30_64_27";
  case VIC::VIC75_1920_1080_P_50_64_27:
    return "VIC75_1920_1080_P_50_64_27";
  case VIC::VIC76_1920_1080_P_60_64_27:
    return "VIC76_1920_1080_P_60_64_27";
  case VIC::VIC77_1920_1080_P_100_64_27:
    return "VIC77_1920_1080_P_100_64_27";
  case VIC::VIC78_1920_1080_P_120_64_27:
    return "VIC78_1920_1080_P_120_64_27";
  case VIC::VIC79_1680_720_P_24_64_27:
    return "VIC79_1680_720_P_24_64_27";
  case VIC::VIC80_1680_720_P_25_64_27:
    return "VIC80_1680_720_P_25_64_27";
  case VIC::VIC81_1680_720_P_30_64_27:
    return "VIC81_1680_720_P_30_64_27";
  case VIC::VIC82_1680_720_P_50_64_27:
    return "VIC82_1680_720_P_50_64_27";
  case VIC::VIC83_1680_720_P_60_64_27:
    return "VIC83_1680_720_P_60_64_27";
  case VIC::VIC84_1680_720_P_100_64_27:
    return "VIC84_1680_720_P_100_64_27";
  case VIC::VIC85_1680_720_P_120_64_27:
    return "VIC85_1680_720_P_120_64_27";
  case VIC::VIC86_2560_1080_P_24_64_27:
    return "VIC86_2560_1080_P_24_64_27";
  case VIC::VIC87_2560_1080_P_25_64_27:
    return "VIC87_2560_1080_P_25_64_27";
  case VIC::VIC88_2560_1080_P_30_64_27:
    return "VIC88_2560_1080_P_30_64_27";
  case VIC::VIC89_2560_1080_P_50_64_27:
    return "VIC89_2560_1080_P_50_64_27";
  case VIC::VIC90_2560_1080_P_60_64_27:
    return "VIC90_2560_1080_P_60_64_27";
  case VIC::VIC91_2560_1080_P_100_64_27:
    return "VIC91_2560_1080_P_100_64_27";
  case VIC::VIC92_2560_1080_P_120_64_27:
    return "VIC92_2560_1080_P_120_64_27";
  case VIC::VIC93_3840_2160_P_24_16_9:
    return "VIC93_3840_2160_P_24_16_9";
  case VIC::VIC94_3840_2160_P_25_16_9:
    return "VIC94_3840_2160_P_25_16_9";
  case VIC::VIC95_3840_2160_P_30_16_9:
    return "VIC95_3840_2160_P_30_16_9";
  case VIC::VIC96_3840_2160_P_50_16_9:
    return "VIC96_3840_2160_P_50_16_9";
  case VIC::VIC97_3840_2160_P_60_16_9:
    return "VIC97_3840_2160_P_60_16_9";
  case VIC::VIC98_4096_2160_P_24_256_135:
    return "VIC98_4096_2160_P_24_256_135";
  case VIC::VIC99_4096_2160_P_25_256_135:
    return "VIC99_4096_2160_P_25_256_135";
  case VIC::VIC100_4096_2160_P_30_256_135:
    return "VIC100_4096_2160_P_30_256_135";
  case VIC::VIC101_4096_2160_P_50_256_135:
    return "VIC101_4096_2160_P_50_256_135";
  case VIC::VIC102_4096_2160_P_60_256_135:
    return "VIC102_4096_2160_P_60_256_135";
  case VIC::VIC103_3840_2160_P_24_64_27:
    return "VIC103_3840_2160_P_24_64_27";
  case VIC::VIC104_3840_2160_P_25_64_27:
    return "VIC104_3840_2160_P_25_64_27";
  case VIC::VIC105_3840_2160_P_30_64_27:
    return "VIC105_3840_2160_P_30_64_27";
  case VIC::VIC106_3840_2160_P_50_64_27:
    return "VIC106_3840_2160_P_50_64_27";
  case VIC::VIC107_3840_2160_P_60_64_27:
    return "VIC107_3840_2160_P_60_64_27";
  case VIC::VIC108_1280_720_P_48_16_9:
    return "VIC108_1280_720_P_48_16_9";
  case VIC::VIC109_1280_720_P_48_64_27:
    return "VIC109_1280_720_P_48_64_27";
  case VIC::VIC110_1680_720_P_48_64_27:
    return "VIC110_1680_720_P_48_64_27";
  case VIC::VIC111_1920_1080_P_48_16_9:
    return "VIC111_1920_1080_P_48_16_9";
  case VIC::VIC112_1920_1080_P_48_64_27:
    return "VIC112_1920_1080_P_48_64_27";
  case VIC::VIC113_2560_1080_P_48_64_27:
    return "VIC113_2560_1080_P_48_64_27";
  case VIC::VIC114_3840_2160_P_48_16_9:
    return "VIC114_3840_2160_P_48_16_9";
  case VIC::VIC115_4096_2160_P_48_256_135:
    return "VIC115_4096_2160_P_48_256_135";
  case VIC::VIC116_3840_2160_P_48_64_27:
    return "VIC116_3840_2160_P_48_64_27";
  case VIC::VIC117_3840_2160_P_100_16_9:
    return "VIC117_3840_2160_P_100_16_9";
  case VIC::VIC118_3840_2160_P_120_16_9:
    return "VIC118_3840_2160_P_120_16_9";
  case VIC::VIC119_3840_2160_P_100_64_27:
    return "VIC119_3840_2160_P_100_64_27";
  case VIC::VIC120_3840_2160_P_120_64_27:
    return "VIC120_3840_2160_P_120_64_27";
  case VIC::VIC121_5120_2160_P_24_64_27:
    return "VIC121_5120_2160_P_24_64_27";
  case VIC::VIC122_5120_2160_P_25_64_27:
    return "VIC122_5120_2160_P_25_64_27";
  case VIC::VIC123_5120_2160_P_30_64_27:
    return "VIC123_5120_2160_P_30_64_27";
  case VIC::VIC124_5120_2160_P_48_64_27:
    return "VIC124_5120_2160_P_48_64_27";
  case VIC::VIC125_5120_2160_P_50_64_27:
    return "VIC125_5120_2160_P_50_64_27";
  case VIC::VIC126_5120_2160_P_60_64_27:
    return "VIC126_5120_2160_P_60_64_27";
  case VIC::VIC127_5120_2160_P_100_64_27:
    return "VIC127_5120_2160_P_100_64_27";
  case VIC::VIC193_5120_2160_P_120_64_27:
    return "VIC193_5120_2160_P_120_64_27";
  case VIC::VIC194_7680_4320_P_24_16_9:
    return "VIC194_7680_4320_P_24_16_9";
  case VIC::VIC195_7680_4320_P_25_16_9:
    return "VIC195_7680_4320_P_25_16_9";
  case VIC::VIC196_7680_4320_P_30_16_9:
    return "VIC196_7680_4320_P_30_16_9";
  case VIC::VIC197_7680_4320_P_48_16_9:
    return "VIC197_7680_4320_P_48_16_9";
  case VIC::VIC198_7680_4320_P_50_16_9:
    return "VIC198_7680_4320_P_50_16_9";
  case VIC::VIC199_7680_4320_P_60_16_9:
    return "VIC199_7680_4320_P_60_16_9";
  case VIC::VIC200_7680_4320_P_100_16_9:
    return "VIC200_7680_4320_P_100_16_9";
  case VIC::VIC201_7680_4320_P_120_16_9:
    return "VIC201_7680_4320_P_120_16_9";
  case VIC::VIC202_7680_4320_P_24_64_27:
    return "VIC202_7680_4320_P_24_64_27";
  case VIC::VIC203_7680_4320_P_25_64_27:
    return "VIC203_7680_4320_P_25_64_27";
  case VIC::VIC204_7680_4320_P_30_64_27:
    return "VIC204_7680_4320_P_30_64_27";
  case VIC::VIC205_7680_4320_P_48_64_27:
    return "VIC205_7680_4320_P_48_64_27";
  case VIC::VIC206_7680_4320_P_50_64_27:
    return "VIC206_7680_4320_P_50_64_27";
  case VIC::VIC207_7680_4320_P_60_64_27:
    return "VIC207_7680_4320_P_60_64_27";
  case VIC::VIC208_7680_4320_P_100_64_27:
    return "VIC208_7680_4320_P_100_64_27";
  case VIC::VIC209_7680_4320_P_120_64_27:
    return "VIC209_7680_4320_P_120_64_27";
  case VIC::VIC210_10240_4320_P_24_64_27:
    return "VIC210_10240_4320_P_24_64_27";
  case VIC::VIC211_10240_4320_P_25_64_27:
    return "VIC211_10240_4320_P_25_64_27";
  case VIC::VIC212_10240_4320_P_30_64_27:
    return "VIC212_10240_4320_P_30_64_27";
  case VIC::VIC213_10240_4320_P_48_64_27:
    return "VIC213_10240_4320_P_48_64_27";
  case VIC::VIC214_10240_4320_P_50_64_27:
    return "VIC214_10240_4320_P_50_64_27";
  case VIC::VIC215_10240_4320_P_60_64_27:
    return "VIC215_10240_4320_P_60_64_27";
  case VIC::VIC216_10240_4320_P_100_64_27:
    return "VIC216_10240_4320_P_100_64_27";
  case VIC::VIC217_10240_4320_P_120_64_27:
    return "VIC217_10240_4320_P_120_64_27";
  case VIC::VIC218_4096_2160_P_100_256_135:
    return "VIC218_4096_2160_P_100_256_135";
  case VIC::VIC219_4096_2160_P_120_256_135:
    return "VIC219_4096_2160_P_120_256_135";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmioutput::VIC, 155> enum_values<::com::rdk::hal::hdmioutput::VIC> = {
  ::com::rdk::hal::hdmioutput::VIC::VIC0_UNAVAILABLE,
  ::com::rdk::hal::hdmioutput::VIC::VIC1_640_480_P_60_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC2_720_480_P_60_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC3_720_480_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC4_1280_720_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC5_1920_1080_I_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC6_720_1440_480_I_60_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC7_720_1440_480_I_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC8_720_1440_240_P_60_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC9_720_1440_240_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC10_2880_480_I_60_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC11_2880_480_I_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC12_2880_240_P_60_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC13_2880_240_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC14_1440_480_P_60_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC15_1440_480_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC16_1920_1080_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC17_720_576_P_50_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC18_720_576_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC19_1280_720_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC20_1920_1080_I_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC21_720_1440_576_I_50_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC22_720_1440_576_I_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC23_720_1440_288_P_50_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC24_720_1440_288_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC25_2880_576_I_50_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC26_2880_576_I_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC27_2880_288_P_50_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC28_2880_288_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC29_1440_576_P_50_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC30_1440_576_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC31_1920_1080_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC32_1920_1080_P_24_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC33_1920_1080_P_25_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC34_1920_1080_P_30_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC35_2880_480_P_60_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC36_2880_480_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC37_2880_576_P_50_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC38_2880_576_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC39_1920_1080_I_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC40_1920_1080_I_100_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC41_1280_720_P_100_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC42_720_576_P_100_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC43_720_576_P_100_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC44_720_1440_576_I_100_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC45_720_1440_576_I_100_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC46_1920_1080_I_120_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC47_1280_720_P_120_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC48_720_480_P_120_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC49_720_480_P_120_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC50_720_1440_480_I_120_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC51_720_1440_480_I_120_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC52_720_576_P_200_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC53_720_576_P_200_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC54_720_1440_576_I_200_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC55_720_1440_576_I_200_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC56_720_480_P_240_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC57_720_480_P_240_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC58_720_1440_480_I_240_4_3,
  ::com::rdk::hal::hdmioutput::VIC::VIC59_720_1440_480_I_240_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC60_1280_720_P_24_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC61_1280_720_P_25_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC62_1280_720_P_30_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC63_1920_1080_P_120_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC64_1920_1080_P_100_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC65_1280_720_P_24_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC66_1280_720_P_25_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC67_1280_720_P_30_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC68_1280_720_P_50_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC69_1280_720_P_60_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC70_1280_720_P_100_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC71_1280_720_P_120_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC72_1920_1080_P_24_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC73_1920_1080_P_25_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC74_1920_1080_P_30_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC75_1920_1080_P_50_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC76_1920_1080_P_60_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC77_1920_1080_P_100_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC78_1920_1080_P_120_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC79_1680_720_P_24_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC80_1680_720_P_25_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC81_1680_720_P_30_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC82_1680_720_P_50_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC83_1680_720_P_60_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC84_1680_720_P_100_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC85_1680_720_P_120_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC86_2560_1080_P_24_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC87_2560_1080_P_25_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC88_2560_1080_P_30_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC89_2560_1080_P_50_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC90_2560_1080_P_60_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC91_2560_1080_P_100_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC92_2560_1080_P_120_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC93_3840_2160_P_24_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC94_3840_2160_P_25_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC95_3840_2160_P_30_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC96_3840_2160_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC97_3840_2160_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC98_4096_2160_P_24_256_135,
  ::com::rdk::hal::hdmioutput::VIC::VIC99_4096_2160_P_25_256_135,
  ::com::rdk::hal::hdmioutput::VIC::VIC100_4096_2160_P_30_256_135,
  ::com::rdk::hal::hdmioutput::VIC::VIC101_4096_2160_P_50_256_135,
  ::com::rdk::hal::hdmioutput::VIC::VIC102_4096_2160_P_60_256_135,
  ::com::rdk::hal::hdmioutput::VIC::VIC103_3840_2160_P_24_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC104_3840_2160_P_25_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC105_3840_2160_P_30_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC106_3840_2160_P_50_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC107_3840_2160_P_60_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC108_1280_720_P_48_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC109_1280_720_P_48_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC110_1680_720_P_48_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC111_1920_1080_P_48_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC112_1920_1080_P_48_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC113_2560_1080_P_48_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC114_3840_2160_P_48_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC115_4096_2160_P_48_256_135,
  ::com::rdk::hal::hdmioutput::VIC::VIC116_3840_2160_P_48_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC117_3840_2160_P_100_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC118_3840_2160_P_120_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC119_3840_2160_P_100_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC120_3840_2160_P_120_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC121_5120_2160_P_24_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC122_5120_2160_P_25_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC123_5120_2160_P_30_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC124_5120_2160_P_48_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC125_5120_2160_P_50_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC126_5120_2160_P_60_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC127_5120_2160_P_100_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC193_5120_2160_P_120_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC194_7680_4320_P_24_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC195_7680_4320_P_25_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC196_7680_4320_P_30_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC197_7680_4320_P_48_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC198_7680_4320_P_50_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC199_7680_4320_P_60_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC200_7680_4320_P_100_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC201_7680_4320_P_120_16_9,
  ::com::rdk::hal::hdmioutput::VIC::VIC202_7680_4320_P_24_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC203_7680_4320_P_25_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC204_7680_4320_P_30_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC205_7680_4320_P_48_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC206_7680_4320_P_50_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC207_7680_4320_P_60_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC208_7680_4320_P_100_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC209_7680_4320_P_120_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC210_10240_4320_P_24_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC211_10240_4320_P_25_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC212_10240_4320_P_30_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC213_10240_4320_P_48_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC214_10240_4320_P_50_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC215_10240_4320_P_60_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC216_10240_4320_P_100_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC217_10240_4320_P_120_64_27,
  ::com::rdk::hal::hdmioutput::VIC::VIC218_4096_2160_P_100_256_135,
  ::com::rdk::hal::hdmioutput::VIC::VIC219_4096_2160_P_120_256_135,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
