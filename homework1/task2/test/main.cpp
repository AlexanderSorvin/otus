#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    /* Чтение шаблона /^(\d+)\.(\d+)\.(\d+)\.(\d+)\t.+?\t.+?$/ */
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}