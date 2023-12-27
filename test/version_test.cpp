#include <gtest/gtest.h>
#include "../lib.hpp"

TEST(VersionTest, BasicAssertions) {
  // Expect equality.
  EXPECT_NE(version(), 100);
}
