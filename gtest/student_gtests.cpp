#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strdup) {
    char* result = String::strdup("test");
    EXPECT_STREQ(result, "test");
    delete[] result; // Remember to free the memory allocated by strdup
}

TEST(StringFunction, strncpy) {
    char dest[10] = {};
    String::strncpy(dest, "hello", 5);
    EXPECT_STREQ(dest, "hello");

    String::strncpy(dest, "world", 3);
    EXPECT_EQ(dest[0], 'w');
    EXPECT_EQ(dest[1], 'o');
    EXPECT_EQ(dest[2], 'r');
    EXPECT_EQ(dest[3], '\0'); // Ensure it's null-terminated
}

TEST(StringFunction, strcat) {
    char dest[10] = "hi";
    String::strcat(dest, ", ");
    String::strcat(dest, "there");
    EXPECT_STREQ(dest, "hi, there");
}

TEST(StringFunction, strncat) {
    char dest[15] = "hello";
    String::strncat(dest, " world", 6);
    EXPECT_STREQ(dest, "hello world");

    String::strncat(dest, "!!!", 2); // Intentionally limiting to 2 characters
    EXPECT_STREQ(dest, "hello world!!");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("abc", "abc"), 0);
    EXPECT_LT(String::strcmp("abc", "bcd"), 0);
    EXPECT_GT(String::strcmp("bcd", "abc"), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("abc", "abc", 3), 0);
    EXPECT_EQ(String::strncmp("abcde", "abcxy", 3), 0);
    EXPECT_LT(String::strncmp("abc", "bcd", 3), 0);
    EXPECT_GT(String::strncmp("bcd", "abc", 3), 0);
    EXPECT_EQ(String::strncmp("hello", "hello", 5), 0);
    EXPECT_NE(String::strncmp("hello", "world", 5), 0);
    EXPECT_EQ(String::strncmp("hello", "hel", 3), 0);
    EXPECT_EQ(String::strncmp("", "", 0), 0);
}

TEST(StringFunction, reverse_cpy) {
    char dest[5];
    String::reverse_cpy(dest, "abcd");
    EXPECT_STREQ(dest, "dcba");
}

TEST(StringFunction, strchr) {
    const char* str = "hello world";
    const char* result = String::strchr(str, 'w');
    EXPECT_STREQ(result, "world");

    result = String::strchr(str, 'z');
    EXPECT_EQ(result, nullptr);
}

TEST(StringFunction, strstr) {
    const char* haystack = "hello world";
    const char* needle = "world";
    const char* result = String::strstr(haystack, needle);
    EXPECT_STREQ(result, "world");

    needle = "planet";
    result = String::strstr(haystack, needle);
    EXPECT_EQ(result, nullptr);

    EXPECT_EQ(String::strstr("hello", "hello"), "hello");

    const char* str = "hello world";
    EXPECT_EQ(String::strstr(str, "world") - str, 6);
    EXPECT_EQ(String::strstr("hello", "world"), nullptr);

    const char* str2 = "hello";
    EXPECT_EQ(String::strstr(str2, ""), str2);
    EXPECT_EQ(String::strstr("", "world"), nullptr);
}
