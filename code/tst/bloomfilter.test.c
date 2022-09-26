#include "../lib/unity/src/unity.h"
#include "../src/bloomfilter.h"
#include "../src/bloomfilter.c"

#define NUM_BITS    1000

void setUp(void)
{

}

void tearDown(void)
{

}

void test_insert(void)
{
    bloomfilt_t * bf = bloomfilter_init(NUM_BITS);

    char * a = "anya is a badass";
    char * b = "rice university";

    TEST_ASSERT_FALSE(bloomfilter_check(bf, a));
    TEST_ASSERT_FALSE(bloomfilter_check(bf, b));

    bloomfilter_insert(bf, a);
    
    TEST_ASSERT_TRUE(bloomfilter_check(bf, a));
    TEST_ASSERT_FALSE(bloomfilter_check(bf, b)); //Could theoretically be true, but this should be unlikely.
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_insert);
    return UNITY_END();
}
