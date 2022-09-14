#include "../lib/unity/src/unity.h"
#include "../src/bitarr.h"

#define NUM_BITS 100

void setUp(void)
{

}

void tearDown(void)
{

}

void test_set_evens(void)
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

void test_unset(void)
{
  int i;
  bitarr_t * b = bitarr_init(NUM_BITS);

  /* Set all even bits */
  for(i = 0; i < NUM_BITS; i += 2) {
    bitarr_set(b, i);
  }

  /* Unset every fourth bits */
  for(i = 0; i < NUM_BITS; i += 4) {
    bitarr_unset(b, i);
  }

  /* Ensure all bits are set as expected */
  //Check bytes that should be fully set
  byte_t expected = 0b01000100;
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
    RUN_TEST(test_set_evens);
    RUN_TEST(test_unset);
    return UNITY_END();
}