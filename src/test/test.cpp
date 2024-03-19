#include <gtest/gtest.h>

#include "../model/polish_notation.h"

TEST(PolishNotation, SimpleMathOperations) {
  PolishNotation test;
  std::string str = "10 - 5";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "5");

  str = "10 * 5";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "50");

  str = "10 / 2.5";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "4");

  str = "10 + 2.5";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "12.5");

  str = "10 mod 3";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "1");

  str = "sqrt(4)";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "2");

  str = "86 ^ 4";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "54700816");
}

TEST(PolishNotation, ComplexOperations) {
  PolishNotation test;
  std::string str = "10 * (5 + 6) / sin((10 * 5) - 3)";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "890.1612062276");

  str = "sin((10 * 5) - 3)";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "0.123573122745");

  str = "0.0000002342345 - 0.00000000443204141";
  test.SetStr(str);

  ASSERT_EQ(test.GetResult(), "0.000000229802");
}

TEST(PolishNotation, ErrorsOperations) {
  PolishNotation test;
  std::string str = "10) * (-7";
  test.SetStr(str);

  ASSERT_EQ(test.GetError(), 1);

  str = "10 / 0";
  test.SetStr(str);

  ASSERT_EQ(test.GetError(), 1);

  str = "asin(300)";
  test.SetStr(str);

  ASSERT_EQ(test.GetError(), 1);

  str = "3 mod 3 mod 3";
  test.SetStr(str);

  ASSERT_EQ(test.GetError(), 1);

  str = "sqrt(-4)";
  test.SetStr(str);

  ASSERT_EQ(test.GetError(), 1);

  str = "5 + - (95 * -57)";
  test.SetStr(str);

  ASSERT_EQ(test.GetError(), 1);
}

TEST(PolishNotation, XValues) {
  PolishNotation test;
  std::string str = "x * 10";
  std::string x = "10";
  test.SetStr(str, x);

  ASSERT_EQ(test.GetResult(), "100");

  str = "x * 10";
  x = "";
  test.SetStr(str, x);

  ASSERT_EQ(test.GetError(), 1);

  str = "x * 10";
  test.SetStr(str);

  ASSERT_EQ(test.GetError(), 1);

  str = "-x - 10";
  x = "2";
  test.SetStr(str, x);

  ASSERT_EQ(test.GetResult(), "-12");

  str = "4 - -x";
  x = "-";
  test.SetStr(str, x);
  ASSERT_EQ(test.GetError(), 1);

  str = "4 - -x";
  x = "-2";
  test.SetStr(str, x);
  ASSERT_EQ(test.GetResult(), "2");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}