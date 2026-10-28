#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
// @aidl-doc
/**
 *  @brief     HDMI Video ID Code (VIC) enum.
 *
 *  Reference: HDMI 2.1 Specification, Section 6.x for Video ID Codes.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
enum class VIC : int32_t {
  // @aidl-doc
  /** Unspecified VIC. */
  VIC0_UNAVAILABLE = 0,
  // @aidl-doc
  /** 640x480p                59.94Hz/60Hz    4:3     1:1 */
  VIC1_640_480_P_60_4_3 = 1,
  // @aidl-doc
  /** 720x480p                59.94Hz/60Hz    4:3     8:9 */
  VIC2_720_480_P_60_4_3 = 2,
  // @aidl-doc
  /** 720x480p                59.94Hz/60Hz    16:9    32:27 */
  VIC3_720_480_P_60_16_9 = 3,
  // @aidl-doc
  /** 1280x720p               59.94Hz/60Hz    16:9    1:1 */
  VIC4_1280_720_P_60_16_9 = 4,
  // @aidl-doc
  /** 1920x1080i              59.94Hz/60Hz    16:9    1:1 */
  VIC5_1920_1080_I_60_16_9 = 5,
  // @aidl-doc
  /** 720(1440)x480i          59.94Hz/60Hz    4:3     8:9 */
  VIC6_720_1440_480_I_60_4_3 = 6,
  // @aidl-doc
  /** 720(1440)x480i          59.94Hz/60Hz    16:9    32:27 */
  VIC7_720_1440_480_I_60_16_9 = 7,
  // @aidl-doc
  /** 720(1440)x240p          59.94Hz/60Hz    4:3     4:9 */
  VIC8_720_1440_240_P_60_4_3 = 8,
  // @aidl-doc
  /** 720(1440)x240p          59.94Hz/60Hz    16:9    16:27 */
  VIC9_720_1440_240_P_60_16_9 = 9,
  // @aidl-doc
  /** 2880x480i               59.94Hz/60Hz    4:3     2:9 - 20:9 */
  VIC10_2880_480_I_60_4_3 = 10,
  // @aidl-doc
  /** 2880x480i               59.94Hz/60Hz    16:9    8:27 - 80:27 */
  VIC11_2880_480_I_60_16_9 = 11,
  // @aidl-doc
  /** 2880x240p               59.94Hz/60Hz    4:3     1:9 - 10:9 */
  VIC12_2880_240_P_60_4_3 = 12,
  // @aidl-doc
  /** 2880x240p               59.94Hz/60Hz    16:9    4:27 - 40:27 */
  VIC13_2880_240_P_60_16_9 = 13,
  // @aidl-doc
  /** 1440x480p               59.94Hz/60Hz    4:3     4:9 or 8:9 */
  VIC14_1440_480_P_60_4_3 = 14,
  // @aidl-doc
  /** 1440x480p               59.94Hz/60Hz    16:9    16:27 or 32:27 */
  VIC15_1440_480_P_60_16_9 = 15,
  // @aidl-doc
  /** 1920x1080p              59.94Hz/60Hz    16:9    1:1 */
  VIC16_1920_1080_P_60_16_9 = 16,
  // @aidl-doc
  /** 720x576p                50Hz            4:3     16:15 */
  VIC17_720_576_P_50_4_3 = 17,
  // @aidl-doc
  /** 720x576p                50Hz            16:9    64:45 */
  VIC18_720_576_P_50_16_9 = 18,
  // @aidl-doc
  /** 1280x720p               50Hz            16:9    1:1 */
  VIC19_1280_720_P_50_16_9 = 19,
  // @aidl-doc
  /** 1920x1080i              50Hz            16:9    1:1 */
  VIC20_1920_1080_I_50_16_9 = 20,
  // @aidl-doc
  /** 720(1440)x576i          50Hz            4:3     16:15 */
  VIC21_720_1440_576_I_50_4_3 = 21,
  // @aidl-doc
  /** 720(1440)x576i          50Hz            16:9    64:45 */
  VIC22_720_1440_576_I_50_16_9 = 22,
  // @aidl-doc
  /** 720(1440)x288p          50Hz            4:3     8:15 */
  VIC23_720_1440_288_P_50_4_3 = 23,
  // @aidl-doc
  /** 720(1440)x288p          50Hz            16:9    32:45 */
  VIC24_720_1440_288_P_50_16_9 = 24,
  // @aidl-doc
  /** 2880x576i               50Hz            4:3     2:15 - 20:15 */
  VIC25_2880_576_I_50_4_3 = 25,
  // @aidl-doc
  /** 2880x576i               50Hz            16:9    16:45 - 160:45 */
  VIC26_2880_576_I_50_16_9 = 26,
  // @aidl-doc
  /** 2880x288p               50Hz            4:3     1:15 - 10:15 */
  VIC27_2880_288_P_50_4_3 = 27,
  // @aidl-doc
  /** 2880x288p               50Hz            16:9    8:45 - 80:45 */
  VIC28_2880_288_P_50_16_9 = 28,
  // @aidl-doc
  /** 1440x576p               50Hz            4:3     8:15 or 16:15 */
  VIC29_1440_576_P_50_4_3 = 29,
  // @aidl-doc
  /** 1440x576p               50Hz            16:9    32:45 or 64:45 */
  VIC30_1440_576_P_50_16_9 = 30,
  // @aidl-doc
  /** 1920x1080p              50Hz            16:9    1:1 */
  VIC31_1920_1080_P_50_16_9 = 31,
  // @aidl-doc
  /** 1920x1080p              23.98Hz/24Hz    16:9    1:1 */
  VIC32_1920_1080_P_24_16_9 = 32,
  // @aidl-doc
  /** 1920x1080p              25Hz            16:9    1:1 */
  VIC33_1920_1080_P_25_16_9 = 33,
  // @aidl-doc
  /** 1920x1080p              29.97Hz/30Hz    16:9    1:1 */
  VIC34_1920_1080_P_30_16_9 = 34,
  // @aidl-doc
  /** 2880x480p               59.94Hz/60Hz    4:3     2:9, 4:9, or 8:9 */
  VIC35_2880_480_P_60_4_3 = 35,
  // @aidl-doc
  /** 2880x480p               59.94Hz/60Hz    16:9    8:27, 16:27, or 32:27 */
  VIC36_2880_480_P_60_16_9 = 36,
  // @aidl-doc
  /** 2880x576p               50Hz            4:3     4:15, 8:15, or 16:15 */
  VIC37_2880_576_P_50_4_3 = 37,
  // @aidl-doc
  /** 2880x576p               50Hz            16:9    16:45, 32:45, or 64:45 */
  VIC38_2880_576_P_50_16_9 = 38,
  // @aidl-doc
  /** 1920x1080i (1250 total) 50Hz            16:9    1:1 */
  VIC39_1920_1080_I_50_16_9 = 39,
  // @aidl-doc
  /** 1920x1080i              100Hz           16:9    1:1 */
  VIC40_1920_1080_I_100_16_9 = 40,
  // @aidl-doc
  /** 1280x720p               100Hz           16:9    1:1 */
  VIC41_1280_720_P_100_16_9 = 41,
  // @aidl-doc
  /** 720x576p                100Hz           4:3     16:15 */
  VIC42_720_576_P_100_4_3 = 42,
  // @aidl-doc
  /** 720x576p                100Hz           16:9    64:45 */
  VIC43_720_576_P_100_16_9 = 43,
  // @aidl-doc
  /** 720(1440)x576i          100Hz           4:3     16:15 */
  VIC44_720_1440_576_I_100_4_3 = 44,
  // @aidl-doc
  /** 720(1440)x576i          100Hz           16:9    64:45 */
  VIC45_720_1440_576_I_100_16_9 = 45,
  // @aidl-doc
  /** 1920x1080i              119.88Hz/120Hz  16:9    1:1 */
  VIC46_1920_1080_I_120_16_9 = 46,
  // @aidl-doc
  /** 1280x720p               119.88Hz/120Hz  16:9    1:1 */
  VIC47_1280_720_P_120_16_9 = 47,
  // @aidl-doc
  /** 720x480p                119.88Hz/120Hz  4:3     8:9 */
  VIC48_720_480_P_120_4_3 = 48,
  // @aidl-doc
  /** 720x480p                119.88Hz/120Hz  16:9    32:27 */
  VIC49_720_480_P_120_16_9 = 49,
  // @aidl-doc
  /** 720(1440)x480i          119.88Hz/120Hz  4:3     8:9 */
  VIC50_720_1440_480_I_120_4_3 = 50,
  // @aidl-doc
  /** 720(1440)x480i          119.88Hz/120Hz  16:9    32:27 */
  VIC51_720_1440_480_I_120_16_9 = 51,
  // @aidl-doc
  /** 720x576p                200Hz           4:3     16:15 */
  VIC52_720_576_P_200_4_3 = 52,
  // @aidl-doc
  /** 720x576p                200Hz           16:9    64:45 */
  VIC53_720_576_P_200_16_9 = 53,
  // @aidl-doc
  /** 720(1440)x576i          200Hz           4:3     16:15 */
  VIC54_720_1440_576_I_200_4_3 = 54,
  // @aidl-doc
  /** 720(1440)x576i          200Hz           16:9    64:45 */
  VIC55_720_1440_576_I_200_16_9 = 55,
  // @aidl-doc
  /** 720x480p                239.76Hz/240Hz  4:3     8:9 */
  VIC56_720_480_P_240_4_3 = 56,
  // @aidl-doc
  /** 720x480p                239.76Hz/240Hz  16:9    32:27 */
  VIC57_720_480_P_240_16_9 = 57,
  // @aidl-doc
  /** 720(1440)x480i          239.76Hz/240Hz  4:3     8:9 */
  VIC58_720_1440_480_I_240_4_3 = 58,
  // @aidl-doc
  /** 720(1440)x480i          239.76Hz/240Hz  16:9    32:27 */
  VIC59_720_1440_480_I_240_16_9 = 59,
  // @aidl-doc
  /** 1280x720p               23.98Hz/24Hz    16:9    1:1 */
  VIC60_1280_720_P_24_16_9 = 60,
  // @aidl-doc
  /** 1280x720p               25Hz            16:9    1:1 */
  VIC61_1280_720_P_25_16_9 = 61,
  // @aidl-doc
  /** 1280x720p               29.97Hz/30Hz    16:9    1:1 */
  VIC62_1280_720_P_30_16_9 = 62,
  // @aidl-doc
  /** 1920x1080p              119.88Hz/120Hz  16:9    1:1 */
  VIC63_1920_1080_P_120_16_9 = 63,
  // @aidl-doc
  /** 1920x1080p              100Hz           16:9    1:1 */
  VIC64_1920_1080_P_100_16_9 = 64,
  // @aidl-doc
  /** 1280x720p               23.98Hz/24Hz    64:27   4:3 */
  VIC65_1280_720_P_24_64_27 = 65,
  // @aidl-doc
  /** 1280x720p               25Hz            64:27   4:3 */
  VIC66_1280_720_P_25_64_27 = 66,
  // @aidl-doc
  /** 1280x720p               29.97Hz/30Hz    64:27   4:3 */
  VIC67_1280_720_P_30_64_27 = 67,
  // @aidl-doc
  /** 1280x720p               50Hz            64:27   4:3 */
  VIC68_1280_720_P_50_64_27 = 68,
  // @aidl-doc
  /** 1280x720p               59.94Hz/60Hz    64:27   4:3 */
  VIC69_1280_720_P_60_64_27 = 69,
  // @aidl-doc
  /** 1280x720p               100Hz           64:27   4:3 */
  VIC70_1280_720_P_100_64_27 = 70,
  // @aidl-doc
  /** 1280x720p               119.88Hz/120Hz  64:27   4:3 */
  VIC71_1280_720_P_120_64_27 = 71,
  // @aidl-doc
  /** 1920x1080p              23.98Hz/24Hz    64:27   4:3 */
  VIC72_1920_1080_P_24_64_27 = 72,
  // @aidl-doc
  /** 1920x1080p              25Hz            64:27   4:3 */
  VIC73_1920_1080_P_25_64_27 = 73,
  // @aidl-doc
  /** 1920x1080p              29.97Hz/30Hz    64:27   4:3 */
  VIC74_1920_1080_P_30_64_27 = 74,
  // @aidl-doc
  /** 1920x1080p              50Hz            64:27   4:3 */
  VIC75_1920_1080_P_50_64_27 = 75,
  // @aidl-doc
  /** 1920x1080p              59.94Hz/60Hz    64:27   4:3 */
  VIC76_1920_1080_P_60_64_27 = 76,
  // @aidl-doc
  /** 1920x1080p              100Hz           64:27   4:3 */
  VIC77_1920_1080_P_100_64_27 = 77,
  // @aidl-doc
  /** 1920x1080p              119.88Hz/120Hz  64:27   4:3 */
  VIC78_1920_1080_P_120_64_27 = 78,
  // @aidl-doc
  /** 1680x720p               23.98Hz/24Hz    64:27   64:63 */
  VIC79_1680_720_P_24_64_27 = 79,
  // @aidl-doc
  /** 1680x720p               25Hz            64:27   64:63 */
  VIC80_1680_720_P_25_64_27 = 80,
  // @aidl-doc
  /** 1680x720p               29.97Hz/30Hz    64:27   64:63 */
  VIC81_1680_720_P_30_64_27 = 81,
  // @aidl-doc
  /** 1680x720p               50Hz            64:27   64:63 */
  VIC82_1680_720_P_50_64_27 = 82,
  // @aidl-doc
  /** 1680x720p               59.94Hz/60Hz    64:27   64:63 */
  VIC83_1680_720_P_60_64_27 = 83,
  // @aidl-doc
  /** 1680x720p               100Hz           64:27   64:63 */
  VIC84_1680_720_P_100_64_27 = 84,
  // @aidl-doc
  /** 1680x720p               119.88Hz/120Hz  64:27   64:63 */
  VIC85_1680_720_P_120_64_27 = 85,
  // @aidl-doc
  /** 2560x1080p              23.98Hz/24Hz    64:27   1:1 */
  VIC86_2560_1080_P_24_64_27 = 86,
  // @aidl-doc
  /** 2560x1080p              25Hz            64:27   1:1 */
  VIC87_2560_1080_P_25_64_27 = 87,
  // @aidl-doc
  /** 2560x1080p              29.97Hz/30Hz    64:27   1:1 */
  VIC88_2560_1080_P_30_64_27 = 88,
  // @aidl-doc
  /** 2560x1080p              50Hz            64:27   1:1 */
  VIC89_2560_1080_P_50_64_27 = 89,
  // @aidl-doc
  /** 2560x1080p              59.94Hz/60Hz    64:27   1:1 */
  VIC90_2560_1080_P_60_64_27 = 90,
  // @aidl-doc
  /** 2560x1080p              100Hz           64:27   1:1 */
  VIC91_2560_1080_P_100_64_27 = 91,
  // @aidl-doc
  /** 2560x1080p              119.88Hz/120Hz  64:27   1:1 */
  VIC92_2560_1080_P_120_64_27 = 92,
  // @aidl-doc
  /** 3840x2160p              23.98Hz/24Hz    16:9    1:1 */
  VIC93_3840_2160_P_24_16_9 = 93,
  // @aidl-doc
  /** 3840x2160p              25Hz            16:9    1:1 */
  VIC94_3840_2160_P_25_16_9 = 94,
  // @aidl-doc
  /** 3840x2160p              29.97Hz/30Hz    16:9    1:1 */
  VIC95_3840_2160_P_30_16_9 = 95,
  // @aidl-doc
  /** 3840x2160p              50Hz            16:9    1:1 */
  VIC96_3840_2160_P_50_16_9 = 96,
  // @aidl-doc
  /** 3840x2160p              59.94Hz/60Hz    16:9    1:1 */
  VIC97_3840_2160_P_60_16_9 = 97,
  // @aidl-doc
  /** 4096x2160p              23.98Hz/24Hz    256:135 1:1 */
  VIC98_4096_2160_P_24_256_135 = 98,
  // @aidl-doc
  /** 4096x2160p              25Hz            256:135 1:1 */
  VIC99_4096_2160_P_25_256_135 = 99,
  // @aidl-doc
  /** 4096x2160p              29.97Hz/30Hz    256:135 1:1 */
  VIC100_4096_2160_P_30_256_135 = 100,
  // @aidl-doc
  /** 4096x2160p              50Hz            256:135 1:1 */
  VIC101_4096_2160_P_50_256_135 = 101,
  // @aidl-doc
  /** 4096x2160p              59.94Hz/60Hz    256:135 1:1 */
  VIC102_4096_2160_P_60_256_135 = 102,
  // @aidl-doc
  /** 3840x2160p              23.98Hz/24Hz    64:27   4:3 */
  VIC103_3840_2160_P_24_64_27 = 103,
  // @aidl-doc
  /** 3840x2160p              25Hz            64:27   4:3 */
  VIC104_3840_2160_P_25_64_27 = 104,
  // @aidl-doc
  /** 3840x2160p              29.97Hz/30Hz    64:27   4:3 */
  VIC105_3840_2160_P_30_64_27 = 105,
  // @aidl-doc
  /** 3840x2160p              50Hz            64:27   4:3 */
  VIC106_3840_2160_P_50_64_27 = 106,
  // @aidl-doc
  /** 3840x2160p              59.94Hz/60Hz    64:27   4:3 */
  VIC107_3840_2160_P_60_64_27 = 107,
  // @aidl-doc
  /** 1280x720p               47.95Hz/48Hz    16:9    1:1 */
  VIC108_1280_720_P_48_16_9 = 108,
  // @aidl-doc
  /** 1280x720p               47.95Hz/48Hz    64:27   4:3 */
  VIC109_1280_720_P_48_64_27 = 109,
  // @aidl-doc
  /** 1680x720p               47.95Hz/48Hz    64:27   64:63 */
  VIC110_1680_720_P_48_64_27 = 110,
  // @aidl-doc
  /** 1920x1080p              47.95Hz/48Hz    16:9    1:1 */
  VIC111_1920_1080_P_48_16_9 = 111,
  // @aidl-doc
  /** 1920x1080p              47.95Hz/48Hz    64:27   4:3 */
  VIC112_1920_1080_P_48_64_27 = 112,
  // @aidl-doc
  /** 2560x1080p              47.95Hz/48Hz    64:27   1:1 */
  VIC113_2560_1080_P_48_64_27 = 113,
  // @aidl-doc
  /** 3840x2160p              47.95Hz/48Hz    16:9    1:1 */
  VIC114_3840_2160_P_48_16_9 = 114,
  // @aidl-doc
  /** 4096x2160p              47.95Hz/48Hz    256:135 1:1 */
  VIC115_4096_2160_P_48_256_135 = 115,
  // @aidl-doc
  /** 3840x2160p              47.95Hz/48Hz    64:27   4:3 */
  VIC116_3840_2160_P_48_64_27 = 116,
  // @aidl-doc
  /** 3840x2160p              100Hz           16:9    1:1 */
  VIC117_3840_2160_P_100_16_9 = 117,
  // @aidl-doc
  /** 3840x2160p              119.88Hz/120Hz  16:9    1:1 */
  VIC118_3840_2160_P_120_16_9 = 118,
  // @aidl-doc
  /** 3840x2160p              100Hz           64:27   4:3 */
  VIC119_3840_2160_P_100_64_27 = 119,
  // @aidl-doc
  /** 3840x2160p              119.88Hz/120Hz  64:27   4:3 */
  VIC120_3840_2160_P_120_64_27 = 120,
  // @aidl-doc
  /** 5120x2160p              23.98Hz/24Hz    64:27   1:1 */
  VIC121_5120_2160_P_24_64_27 = 121,
  // @aidl-doc
  /** 5120x2160p              25Hz            64:27   1:1 */
  VIC122_5120_2160_P_25_64_27 = 122,
  // @aidl-doc
  /** 5120x2160p              29.97Hz/30Hz    64:27   1:1 */
  VIC123_5120_2160_P_30_64_27 = 123,
  // @aidl-doc
  /** 5120x2160p              47.95Hz/48Hz    64:27   1:1 */
  VIC124_5120_2160_P_48_64_27 = 124,
  // @aidl-doc
  /** 5120x2160p              50Hz            64:27   1:1 */
  VIC125_5120_2160_P_50_64_27 = 125,
  // @aidl-doc
  /** 5120x2160p              59.94Hz/60Hz    64:27   1:1 */
  VIC126_5120_2160_P_60_64_27 = 126,
  // @aidl-doc
  /** 5120x2160p              100Hz           64:27   1:1 */
  VIC127_5120_2160_P_100_64_27 = 127,
  // @aidl-doc
  /** 5120x2160p              119.88Hz/120Hz  64:27   1:1 */
  VIC193_5120_2160_P_120_64_27 = 193,
  // @aidl-doc
  /** 7680x4320p              23.98Hz/24Hz    16:9    1:1 */
  VIC194_7680_4320_P_24_16_9 = 194,
  // @aidl-doc
  /** 7680x4320p              25Hz            16:9    1:1 */
  VIC195_7680_4320_P_25_16_9 = 195,
  // @aidl-doc
  /** 7680x4320p              29.97Hz/30Hz    16:9    1:1 */
  VIC196_7680_4320_P_30_16_9 = 196,
  // @aidl-doc
  /** 7680x4320p              47.95Hz/48Hz    16:9    1:1 */
  VIC197_7680_4320_P_48_16_9 = 197,
  // @aidl-doc
  /** 7680x4320p              50Hz            16:9    1:1 */
  VIC198_7680_4320_P_50_16_9 = 198,
  // @aidl-doc
  /** 7680x4320p              59.94Hz/60Hz    16:9    1:1 */
  VIC199_7680_4320_P_60_16_9 = 199,
  // @aidl-doc
  /** 7680x4320p              100Hz           16:9    1:1 */
  VIC200_7680_4320_P_100_16_9 = 200,
  // @aidl-doc
  /** 7680x4320p              119.88Hz/120Hz  16:9    1:1 */
  VIC201_7680_4320_P_120_16_9 = 201,
  // @aidl-doc
  /** 7680x4320p              23.98Hz/24Hz    64:27   4:3 */
  VIC202_7680_4320_P_24_64_27 = 202,
  // @aidl-doc
  /** 7680x4320p              25Hz            64:27   4:3 */
  VIC203_7680_4320_P_25_64_27 = 203,
  // @aidl-doc
  /** 7680x4320p              29.97Hz/30Hz    64:27   4:3 */
  VIC204_7680_4320_P_30_64_27 = 204,
  // @aidl-doc
  /** 7680x4320p              47.95Hz/48Hz    64:27   4:3 */
  VIC205_7680_4320_P_48_64_27 = 205,
  // @aidl-doc
  /** 7680x4320p              50Hz            64:27   4:3 */
  VIC206_7680_4320_P_50_64_27 = 206,
  // @aidl-doc
  /** 7680x4320p              59.94Hz/60Hz    64:27   4:3 */
  VIC207_7680_4320_P_60_64_27 = 207,
  // @aidl-doc
  /** 7680x4320p              100Hz           64:27   4:3 */
  VIC208_7680_4320_P_100_64_27 = 208,
  // @aidl-doc
  /** 7680x4320p              119.88Hz/120Hz  64:27   4:3 */
  VIC209_7680_4320_P_120_64_27 = 209,
  // @aidl-doc
  /** 10240x4320p             23.98Hz/24Hz    64:27   1:1 */
  VIC210_10240_4320_P_24_64_27 = 210,
  // @aidl-doc
  /** 10240x4320p             25Hz            64:27   1:1 */
  VIC211_10240_4320_P_25_64_27 = 211,
  // @aidl-doc
  /** 10240x4320p             29.97Hz/30Hz    64:27   1:1 */
  VIC212_10240_4320_P_30_64_27 = 212,
  // @aidl-doc
  /** 10240x4320p             47.95Hz/48Hz    64:27   1:1 */
  VIC213_10240_4320_P_48_64_27 = 213,
  // @aidl-doc
  /** 10240x4320p             50Hz            64:27   1:1 */
  VIC214_10240_4320_P_50_64_27 = 214,
  // @aidl-doc
  /** 10240x4320p             59.94Hz/60Hz    64:27   1:1 */
  VIC215_10240_4320_P_60_64_27 = 215,
  // @aidl-doc
  /** 10240x4320p             100Hz           64:27   1:1 */
  VIC216_10240_4320_P_100_64_27 = 216,
  // @aidl-doc
  /** 10240x4320p             119.88Hz/120Hz  64:27   1:1 */
  VIC217_10240_4320_P_120_64_27 = 217,
  // @aidl-doc
  /** 4096x2160p              100Hz           256:135 1:1 */
  VIC218_4096_2160_P_100_256_135 = 218,
  // @aidl-doc
  /** 4096x2160p              119.88Hz/120Hz  256:135 1:1 */
  VIC219_4096_2160_P_120_256_135 = 219,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
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
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmiinput::VIC, 155> enum_values<::com::rdk::hal::hdmiinput::VIC> = {
  ::com::rdk::hal::hdmiinput::VIC::VIC0_UNAVAILABLE,
  ::com::rdk::hal::hdmiinput::VIC::VIC1_640_480_P_60_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC2_720_480_P_60_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC3_720_480_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC4_1280_720_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC5_1920_1080_I_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC6_720_1440_480_I_60_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC7_720_1440_480_I_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC8_720_1440_240_P_60_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC9_720_1440_240_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC10_2880_480_I_60_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC11_2880_480_I_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC12_2880_240_P_60_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC13_2880_240_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC14_1440_480_P_60_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC15_1440_480_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC16_1920_1080_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC17_720_576_P_50_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC18_720_576_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC19_1280_720_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC20_1920_1080_I_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC21_720_1440_576_I_50_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC22_720_1440_576_I_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC23_720_1440_288_P_50_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC24_720_1440_288_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC25_2880_576_I_50_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC26_2880_576_I_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC27_2880_288_P_50_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC28_2880_288_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC29_1440_576_P_50_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC30_1440_576_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC31_1920_1080_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC32_1920_1080_P_24_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC33_1920_1080_P_25_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC34_1920_1080_P_30_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC35_2880_480_P_60_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC36_2880_480_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC37_2880_576_P_50_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC38_2880_576_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC39_1920_1080_I_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC40_1920_1080_I_100_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC41_1280_720_P_100_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC42_720_576_P_100_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC43_720_576_P_100_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC44_720_1440_576_I_100_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC45_720_1440_576_I_100_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC46_1920_1080_I_120_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC47_1280_720_P_120_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC48_720_480_P_120_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC49_720_480_P_120_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC50_720_1440_480_I_120_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC51_720_1440_480_I_120_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC52_720_576_P_200_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC53_720_576_P_200_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC54_720_1440_576_I_200_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC55_720_1440_576_I_200_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC56_720_480_P_240_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC57_720_480_P_240_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC58_720_1440_480_I_240_4_3,
  ::com::rdk::hal::hdmiinput::VIC::VIC59_720_1440_480_I_240_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC60_1280_720_P_24_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC61_1280_720_P_25_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC62_1280_720_P_30_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC63_1920_1080_P_120_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC64_1920_1080_P_100_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC65_1280_720_P_24_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC66_1280_720_P_25_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC67_1280_720_P_30_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC68_1280_720_P_50_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC69_1280_720_P_60_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC70_1280_720_P_100_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC71_1280_720_P_120_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC72_1920_1080_P_24_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC73_1920_1080_P_25_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC74_1920_1080_P_30_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC75_1920_1080_P_50_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC76_1920_1080_P_60_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC77_1920_1080_P_100_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC78_1920_1080_P_120_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC79_1680_720_P_24_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC80_1680_720_P_25_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC81_1680_720_P_30_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC82_1680_720_P_50_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC83_1680_720_P_60_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC84_1680_720_P_100_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC85_1680_720_P_120_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC86_2560_1080_P_24_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC87_2560_1080_P_25_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC88_2560_1080_P_30_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC89_2560_1080_P_50_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC90_2560_1080_P_60_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC91_2560_1080_P_100_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC92_2560_1080_P_120_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC93_3840_2160_P_24_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC94_3840_2160_P_25_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC95_3840_2160_P_30_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC96_3840_2160_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC97_3840_2160_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC98_4096_2160_P_24_256_135,
  ::com::rdk::hal::hdmiinput::VIC::VIC99_4096_2160_P_25_256_135,
  ::com::rdk::hal::hdmiinput::VIC::VIC100_4096_2160_P_30_256_135,
  ::com::rdk::hal::hdmiinput::VIC::VIC101_4096_2160_P_50_256_135,
  ::com::rdk::hal::hdmiinput::VIC::VIC102_4096_2160_P_60_256_135,
  ::com::rdk::hal::hdmiinput::VIC::VIC103_3840_2160_P_24_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC104_3840_2160_P_25_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC105_3840_2160_P_30_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC106_3840_2160_P_50_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC107_3840_2160_P_60_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC108_1280_720_P_48_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC109_1280_720_P_48_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC110_1680_720_P_48_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC111_1920_1080_P_48_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC112_1920_1080_P_48_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC113_2560_1080_P_48_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC114_3840_2160_P_48_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC115_4096_2160_P_48_256_135,
  ::com::rdk::hal::hdmiinput::VIC::VIC116_3840_2160_P_48_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC117_3840_2160_P_100_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC118_3840_2160_P_120_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC119_3840_2160_P_100_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC120_3840_2160_P_120_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC121_5120_2160_P_24_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC122_5120_2160_P_25_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC123_5120_2160_P_30_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC124_5120_2160_P_48_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC125_5120_2160_P_50_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC126_5120_2160_P_60_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC127_5120_2160_P_100_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC193_5120_2160_P_120_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC194_7680_4320_P_24_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC195_7680_4320_P_25_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC196_7680_4320_P_30_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC197_7680_4320_P_48_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC198_7680_4320_P_50_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC199_7680_4320_P_60_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC200_7680_4320_P_100_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC201_7680_4320_P_120_16_9,
  ::com::rdk::hal::hdmiinput::VIC::VIC202_7680_4320_P_24_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC203_7680_4320_P_25_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC204_7680_4320_P_30_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC205_7680_4320_P_48_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC206_7680_4320_P_50_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC207_7680_4320_P_60_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC208_7680_4320_P_100_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC209_7680_4320_P_120_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC210_10240_4320_P_24_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC211_10240_4320_P_25_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC212_10240_4320_P_30_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC213_10240_4320_P_48_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC214_10240_4320_P_50_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC215_10240_4320_P_60_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC216_10240_4320_P_100_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC217_10240_4320_P_120_64_27,
  ::com::rdk::hal::hdmiinput::VIC::VIC218_4096_2160_P_100_256_135,
  ::com::rdk::hal::hdmiinput::VIC::VIC219_4096_2160_P_120_256_135,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
