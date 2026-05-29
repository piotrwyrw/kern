#include <stdio.h>

#define TEST(id) int id##_test()
#define RUN(id)                                                                \
  if (id##_test() != 0) {                                                      \
    printf("[FAIL] " #id "\n");                                                \
    return 1;                                                                  \
  } else {                                                                     \
    printf("[PASSED] " #id "\n");                                              \
  }

TEST(smoke) { return 0; }

int main(void) {
  RUN(smoke)

  printf("All tests passed!\n");
  return 0;
}
