#include <cstdio>
#include "gtest/gtest.h"

void setup() {
  testing::InitGoogleTest();
}

void loop() { RUN_ALL_TESTS(); }

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}