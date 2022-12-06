#include "../lib/unity/src/unity.h"
#include "../src/bitarr/bitarr.h"

#define NUM_BITS 100

void setUp(void)
{

}

void tearDown(void)
{

}

void test_set(void)
{
    int i;
    byte_t * b = INIT_BITARR(NUM_BITS);

    /* Set all even bits */
    for(i = 0; i < NUM_BITS; i += 2) {
      SET_BITARR(b, i);
    }

    /* Ensure all bits are set as expected */
    byte_t expected = 0b01010101;
    //Check bytes that should be fully set
    for(i = 0; i < ROUND_BITS_TO_BYTES(NUM_BITS) - 1; i++) {
      TEST_ASSERT_BITS(0xFF, expected, b[i]);
    }
    //Check last byte, which could be partially set
    TEST_ASSERT_BITS(0xFF >> (BITS_PER_BYTE - (NUM_BITS % BITS_PER_BYTE)), expected, b[i]);

    FREE_BITARR(b);
}

void test_check(void)
{
  unsigned i = 0;
  byte_t * b = INIT_BITARR(NUM_BITS);

  int n = 6;
  int indexes[] = {0,3,7,8,NUM_BITS/2, NUM_BITS-1}; 

  for (i = 0; i<n; i++) {
    TEST_ASSERT_FALSE(CHECK_BITARR(b, indexes[i]));
    SET_BITARR(b, indexes[i]);
    TEST_ASSERT_TRUE(CHECK_BITARR(b, indexes[i]));

  }

  FREE_BITARR(b);
}


void test_unset(void)
{
    int i;
    byte_t * b = INIT_BITARR(NUM_BITS);

    /* Set all even bits */
    for(i = 0; i < NUM_BITS; i += 2) {
      SET_BITARR(b, i);
    }

    /* Ensure all bits are set as expected */
    byte_t expected = 0b01010101;
    //Check bytes that should be fully set
    for(i = 0; i < ROUND_BITS_TO_BYTES(NUM_BITS) - 1; i++) {
      TEST_ASSERT_BITS(0xFF, expected, b[i]);
    }
    //Check last byte, which could be partially set
    TEST_ASSERT_BITS(0xFF >> (BITS_PER_BYTE - (NUM_BITS % BITS_PER_BYTE)), expected, b[i]);

    FREE_BITARR(b);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_set);
    RUN_TEST(test_unset);
    RUN_TEST(test_check);
    return UNITY_END();
}
