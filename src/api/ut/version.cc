#include <gtest/gtest.h>
#include <quicplus/api.h>

#include <iostream>

// NOLINTNEXTLINE
TEST(TestVersion, Test)
{
  auto i = std::stoul(quicplus::GetMajorStr());
  auto num = quicplus::GetMajorNum();
  ASSERT_EQ(i, num);
  i = std::stoul(quicplus::GetMinorStr());
  num = quicplus::GetMinorNum();
  ASSERT_EQ(i, num);
  i = std::stoul(quicplus::GetPatchStr());
  num = quicplus::GetPatchNum();
  ASSERT_EQ(i, num);
  const auto v1 = quicplus::GetMajorStr() + "." + quicplus::GetMinorStr() + "." + quicplus::GetPatchStr();
  const auto v2 = quicplus::GetVersion();
  ASSERT_EQ(v1, v2);
}
