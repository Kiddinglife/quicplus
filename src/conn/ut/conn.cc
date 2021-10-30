#include <gtest/gtest.h>
#include <conn/conn.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

// NOLINTNEXTLINE
TEST(TestOne, LibOne)
{
  std::cout << "Running test on the exported library!" << std::endl;

  conn::SummationSubClass sum_class;
  conn::DifferenceSubClass diff_class;

  constexpr double kTOL = 1e-10;
  constexpr double kOP1 = 15.0;
  constexpr double kOP2 = 10.0;

  double tol = kTOL;
  double op1 = kOP1;
  double op2 = kOP2;

  ASSERT_EQ(fabs(sum_class.DoSomething(op1, op2) - (op1 + op2)) > tol, false);
  ASSERT_EQ(fabs(diff_class.DoSomething(op1, op2) - (op1 - op2)) > tol, false);
}
