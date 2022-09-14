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
    //Check bytes that should be fully set
    for(i = 0; i < b->size - 1; i++) {
      TEST_ASSERT_BITS(0xFF, 0x55, b->arr[i]);
    }
    //Check last byte, which could be partially set
    TEST_ASSERT_BITS(0xFF >> (BITS_PER_BYTE - (NUM_BITS % BITS_PER_BYTE)), 0x55, b->arr[i]);

    bitarr_free(b);
}

// void test_unset(void)
// {
//   TEST_ASSERT_EQUAL_HEX8(80,80);
// }

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_set);
    // RUN_TEST(test_AverageThreeBytes_should_AverageHighValues);
    return UNITY_END();
}