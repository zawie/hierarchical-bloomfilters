#include "../lib/unity/src/unity.h"
#include "../src/h_bloomfilter.h"
#include "../src/h_bloomfilter.c"

#define NUM_BITS    (PAGE_SIZE_BITS*10)

void setUp(void)
{

}

void tearDown(void)
{

}

void test_insert(void)
{
    printf("Initing...\n");
    h_bloomfilt_t * bf = h_bloomfilter_init(NUM_BITS);

    char * a = "anya is a badass";
    char * b = "rice university";

    printf("Pre-checking...\n");
    TEST_ASSERT_FALSE(h_bloomfilter_check(bf, a));
    TEST_ASSERT_FALSE(h_bloomfilter_check(bf, b));

    printf("Inserting...\n");
    h_bloomfilter_insert(bf, a);
    
    printf("Post-checking...\n");
    TEST_ASSERT_TRUE(h_bloomfilter_check(bf, a));
    TEST_ASSERT_FALSE(h_bloomfilter_check(bf, b)); //Could theoretically be true, but this should be unlikely.
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_insert);
    return UNITY_END();
}
