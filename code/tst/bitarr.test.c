#include "../lib/unity/src/unity.h"
#include "../src/bitarr.h"

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
    bitarr_t * b = bitarr_init(NUM_BITS);

    /* Set all even bits */
    for(i = 0; i < NUM_BITS; i += 2) {
      bitarr_set(b, i);
    }

    /* Ensure all bits are set as expected */
    byte_t expected = 0b01010101;
    //Check bytes that should be fully set
    for(i = 0; i < b->size - 1; i++) {
      TEST_ASSERT_BITS(0xFF, expected, b->arr[i]);
    }
    //Check last byte, which could be partially set
    TEST_ASSERT_BITS(0xFF >> (BITS_PER_BYTE - (NUM_BITS % BITS_PER_BYTE)), expected, b->arr[i]);

    bitarr_free(b);
}

void test_check(void)
{
  unsigned i = 0;
  bitarr_t * b = bitarr_init(NUM_BITS);

  int n = 6;
  int indexes[] = {0,3,7,8,NUM_BITS/2, NUM_BITS-1}; 

  for (i = 0; i<n; i++) {
    TEST_ASSERT_FALSE(bitarr_check(b, indexes[i]));
    bitarr_set(b, indexes[i]);
    TEST_ASSERT_TRUE(bitarr_check(b, indexes[i]));

  }

  bitarr_free(b);
}


void test_unset(void)
{
    int i;
    bitarr_t * b = bitarr_init(NUM_BITS);

    /* Set all even bits */
    for(i = 0; i < NUM_BITS; i += 2) {
      bitarr_set(b, i);
    }

    /* Ensure all bits are set as expected */
    byte_t expected = 0b01010101;
    //Check bytes that should be fully set
    for(i = 0; i < b->size - 1; i++) {
      TEST_ASSERT_BITS(0xFF, expected, b->arr[i]);
    }
    //Check last byte, which could be partially set
    TEST_ASSERT_BITS(0xFF >> (BITS_PER_BYTE - (NUM_BITS % BITS_PER_BYTE)), expected, b->arr[i]);

    bitarr_free(b);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_set);
    RUN_TEST(test_unset);
    RUN_TEST(test_check);
    return UNITY_END();
}