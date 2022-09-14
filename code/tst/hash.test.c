#include "../lib/unity/src/unity.h"
#include "../src/hash.h"
#include "../src/hash.djb2.c"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_generate_config(void)
{
    hash_config_t a = generate_hash_config();
    hash_config_t b = generate_hash_config();
    hash_config_t c = generate_hash_config();

    //While it is possible they equal, this should be rare...
    TEST_ASSERT_TRUE(a != b);
    TEST_ASSERT_TRUE(b != c);
    TEST_ASSERT_TRUE(c != a);
}

void test_hash(void)
{
    hash_config_t config = generate_hash_config();

    char * a = "cats are cool";
    char * b = "anya is beautiful";
    char * c = "Rice university";

    //Test that hashing is consitent
    TEST_ASSERT_TRUE(hash(a, config) == hash(a, config));
    TEST_ASSERT_TRUE(hash(b, config) == hash(b, config));
    TEST_ASSERT_TRUE(hash(c, config) == hash(c, config));

    //While it is possible they equal, this should be rare...
    TEST_ASSERT_TRUE(hash(a, config) != hash(b, config));
    TEST_ASSERT_TRUE(hash(b, config) != hash(c, config));
    TEST_ASSERT_TRUE(hash(c, config) != hash(a, config));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_generate_config);
    RUN_TEST(test_hash);
    return UNITY_END();
}