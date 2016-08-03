// This file is distributed under the MIT license.
// See the LICENSE file for details.

#include <cstdint>
#include <cstring> // memcpy

#include <visionaray/math/math.h>

#include <gtest/gtest.h>

using namespace visionaray;


//-------------------------------------------------------------------------------------------------
// Test snorm initialization (single values, arrays)
//

TEST(Snorm, Initialization)
{
    // Some convenience -----------------------------------

    static const int8_t  max8  = numeric_limits<int8_t>::max();
    static const int16_t max16 = numeric_limits<int16_t>::max();
    static const int32_t max32 = numeric_limits<int32_t>::max();

    static const int8_t  low8  = numeric_limits<int8_t>::lowest();
    static const int16_t low16 = numeric_limits<int16_t>::lowest();
    static const int32_t low32 = numeric_limits<int32_t>::lowest();


    // Test initialization --------------------------------

    snorm< 8> sn8;
    snorm<16> sn16;
    snorm<32> sn32;
    snorm< 8> sn8s[4];
    snorm<16> sn16s[4];
    snorm<32> sn32s[4];

    // init with -1

    sn8  = -1.0f;
    sn16 = -1.0f;
    sn32 = -1.0f;

//  EXPECT_EQ(int8_t(sn8),   low8);  // TODO: why does intX_t(snX) yield lowX + 1?? 
//  EXPECT_EQ(int16_t(sn16), low16); // TODO: why does intX_t(snX) yield lowX + 1??
//  EXPECT_EQ(int32_t(sn32), low32); // TODO: why does intX_t(snX) yield lowX + 1??

    EXPECT_FLOAT_EQ(float(sn8),  -1.0f);
    EXPECT_FLOAT_EQ(float(sn16), -1.0f);
    EXPECT_FLOAT_EQ(float(sn32), -1.0f);


    // init with 1

    sn8  = 1.0f;
    sn16 = 1.0f;
    sn32 = 1.0f;

    EXPECT_EQ(int8_t(sn8),   max8);
    EXPECT_EQ(int16_t(sn16), max16);
    EXPECT_EQ(int32_t(sn32), max32);

    EXPECT_FLOAT_EQ(float(sn8),  1.0f);
    EXPECT_FLOAT_EQ(float(sn16), 1.0f);
    EXPECT_FLOAT_EQ(float(sn32), 1.0f);


    // init with byte arrays

    int8_t arr8[]      = { low8,  0, int8_t(max8  / 2),  max8 };
    int16_t arr16[]    = { low16, 0, int8_t(max16 / 2), max16 };
    int32_t arr32[]    = { low32, 0, int8_t(max32 / 2), max32 };

    std::memcpy(sn8s,  arr8,  sizeof(arr8));
    std::memcpy(sn16s, arr16, sizeof(arr16));
    std::memcpy(sn32s, arr32, sizeof(arr32));

    for (int i = 0; i < 4; ++i)
    {
        EXPECT_EQ(int8_t(sn8s[i]),   arr8[i]);
        EXPECT_EQ(int16_t(sn16s[i]), arr16[i]);
        EXPECT_EQ(int32_t(sn32s[i]), arr32[i]);

//      EXPECT_FLOAT_EQ(float(sn8s[i]),  static_cast<float>(arr8[i])  / max8); // TODO
//      EXPECT_FLOAT_EQ(float(sn16s[i]), static_cast<float>(arr16[i]) / max8); // TODO
//      EXPECT_FLOAT_EQ(float(sn32s[i]), static_cast<float>(arr32[i]) / max8); // TODO
    }
}


//-------------------------------------------------------------------------------------------------
// Test comparison operators
//

template <unsigned Bits>
static void test_cmp()
{
    // negative numbers -----------------------------------

    snorm<Bits> a;
    snorm<Bits> b;

    a = -1.0f;
    b = -0.5f;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE( a != b);
    EXPECT_TRUE( a  < b);
    EXPECT_TRUE( a <= b);
    EXPECT_FALSE(a  > b);
    EXPECT_FALSE(a >= b);

    a = -0.5f;
    b = -1.0f;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE( a != b);
    EXPECT_FALSE(a  < b);
    EXPECT_FALSE(a <= b);
    EXPECT_TRUE( a  > b);
    EXPECT_TRUE( a >= b);

    a = -1.0f;
    b = -1.0f;

    EXPECT_TRUE( a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a  < b);
    EXPECT_TRUE( a <= b);
    EXPECT_FALSE(a  > b);
    EXPECT_TRUE( a >= b);

    // all zeros ------------------------------------------

    a = 0.0f;
    b = 0.0f;

    EXPECT_TRUE( a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a  < b);
    EXPECT_TRUE( a <= b);
    EXPECT_FALSE(a  > b);
    EXPECT_TRUE( a >= b);

    // positive numbers -----------------------------------

    a = 0.5f;
    b = 1.0f;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE( a != b);
    EXPECT_TRUE( a  < b);
    EXPECT_TRUE( a <= b);
    EXPECT_FALSE(a  > b);
    EXPECT_FALSE(a >= b);

    a = 1.0f;
    b = 0.5f;

    EXPECT_FALSE(a == b);
    EXPECT_TRUE( a != b);
    EXPECT_FALSE(a  < b);
    EXPECT_FALSE(a <= b);
    EXPECT_TRUE( a  > b);
    EXPECT_TRUE( a >= b);

    a = 1.0f;
    b = 1.0f;

    EXPECT_TRUE( a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a  < b);
    EXPECT_TRUE( a <= b);
    EXPECT_FALSE(a  > b);
    EXPECT_TRUE( a >= b);
}

TEST(Snorm, Comparisons)
{
    test_cmp< 8>();
    test_cmp<16>();
    test_cmp<32>();
}


//-------------------------------------------------------------------------------------------------
// Test numeric limits
// All representations (norm, int, float)
//

TEST(Snorm, NumericLimits)
{
    // Some convenience -----------------------------------

//  static const int8_t   int8_max = numeric_limits<int8_t>::max();
//  static const int16_t int16_max = numeric_limits<int16_t>::max();
//  static const int32_t int32_max = numeric_limits<int32_t>::max();
//
//  static const int8_t  int8_low  = numeric_limits<int8_t>::lowest();
//  static const int16_t int16_low = numeric_limits<int16_t>::lowest();
//  static const int32_t int32_low = numeric_limits<int32_t>::lowest();
//
//  static const int8_t   int8_min = numeric_limits<int8_t>::min();
//  static const int16_t int16_min = numeric_limits<int16_t>::min();
//  static const int32_t int32_min = numeric_limits<int32_t>::min();


    // Normalized reprentation ----------------------------

    EXPECT_TRUE(numeric_limits<snorm< 8>>::max() == snorm< 8>(1.0f));
    EXPECT_TRUE(numeric_limits<snorm<16>>::max() == snorm<16>(1.0f));
    EXPECT_TRUE(numeric_limits<snorm<32>>::max() == snorm<32>(1.0f));

    EXPECT_TRUE(numeric_limits<snorm< 8>>::lowest() == snorm< 8>(-1.0f));
    EXPECT_TRUE(numeric_limits<snorm<16>>::lowest() == snorm<16>(-1.0f));
    EXPECT_TRUE(numeric_limits<snorm<32>>::lowest() == snorm<32>(-1.0f));

    EXPECT_TRUE(numeric_limits<snorm< 8>>::min() == snorm< 8>(0.0f));
    EXPECT_TRUE(numeric_limits<snorm<16>>::min() == snorm<16>(0.0f));
    EXPECT_TRUE(numeric_limits<snorm<32>>::min() == snorm<32>(0.0f));


    // Integer representation -----------------------------

//  EXPECT_EQ(static_cast< int8_t>(numeric_limits<snorm< 8>>::max()), int8_max);
//  EXPECT_EQ(static_cast<int16_t>(numeric_limits<snorm<16>>::max()), int16_max);
//  EXPECT_EQ(static_cast<int32_t>(numeric_limits<snorm<32>>::max()), int32_max);
//
//  EXPECT_EQ(static_cast< int8_t>(numeric_limits<snorm< 8>>::lowest()), int8_low);
//  EXPECT_EQ(static_cast<int16_t>(numeric_limits<snorm<16>>::lowest()), int16_low);
//  EXPECT_EQ(static_cast<int32_t>(numeric_limits<snorm<32>>::lowest()), int32_low);
//
//  EXPECT_EQ(static_cast< int8_t>(numeric_limits<snorm< 8>>::min()), int8_min);
//  EXPECT_EQ(static_cast<int16_t>(numeric_limits<snorm<16>>::min()), int16_min);
//  EXPECT_EQ(static_cast<int32_t>(numeric_limits<snorm<32>>::min()), int32_min);


    // Float representation -------------------------------

    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm< 8>>::max()),     1.0f);
    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm<16>>::max()),     1.0f);
    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm<32>>::max()),     1.0f);

    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm< 8>>::lowest()), -1.0f);
    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm<16>>::lowest()), -1.0f);
    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm<32>>::lowest()), -1.0f);

    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm< 8>>::min()),     0.0f);
    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm<16>>::min()),     0.0f);
    EXPECT_FLOAT_EQ(static_cast<float>(numeric_limits<snorm<32>>::min()),     0.0f);
}
