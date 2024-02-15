#include <gtest/gtest.h>

#include "list.hpp"
using namespace list;

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");
    Node* foo_list = foo_list_head;

    EXPECT_EQ(foo_list->data, 'f');
    // ASSERT instead of EXPECT means: end the test here if this fails, do not try to continue
    // running. This is useful to prevent early crashes.
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);

    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);
}

// Add remaining tests below. All tests should follow
// the format of `TEST(ListTests, <TestName>){}`.

TEST(ListTests, Print) {
    std::ostringstream output;
    Node* const head = list::from_string("test");
    list::print(output, head);
    EXPECT_EQ(output.str(), "test");
    list::free(head);
}

TEST(ListTests, Copy) {
    Node* original = from_string("test");
    Node* copied = copy(original);
    std::ostringstream original_str;
    std::ostringstream copied_str;
    print(original_str, original);
    print(copied_str, copied);
    EXPECT_EQ(original_str.str(), copied_str.str());
    EXPECT_NE(original, copied);
    free(original);
    free(copied);
}

// Test for the compare function
TEST(ListTests, Compare) {
    Node* list1 = from_string("abc");
    Node* list2 = from_string("abc");
    Node* list3 = from_string("abd");
    Node* list4 = from_string("ab");
    EXPECT_EQ(compare(list1, list2), 0);
    EXPECT_LT(compare(list1, list3), 0);
    EXPECT_GT(compare(list3, list1), 0);
    EXPECT_LT(compare(list4, list1), 0);
    free(list1);
    free(list2);
    free(list3);
    free(list4);
}

// Test for the reverse function
TEST(ListTests, Reverse) {
    Node* original = from_string("abc");
    Node* reversed = reverse(original);
    std::ostringstream reversed_str;
    print(reversed_str, reversed);
    EXPECT_EQ(reversed_str.str(), "cba");
    free(original);
    free(reversed);
}

// Test for the append function
TEST(ListTests, Append) {
    Node* list1 = from_string("abc");
    Node* list2 = from_string("def");
    Node* appended = append(list1, list2);
    std::ostringstream appended_str;
    print(appended_str, appended);
    EXPECT_EQ(appended_str.str(), "abcdef");
    free(list1);
    free(list2);
    free(appended);
}

// Test for the index function
TEST(ListTests, Index) {
    Node* list = from_string("hello");
    Node* n = nth(list, 2); // 'l'
    EXPECT_EQ(index(list, n), 2);
    EXPECT_EQ(index(list, nullptr), 5);
    free(list);
}

// Test for the find_char function
TEST(ListTests, FindChar) {
    Node* list = from_string("hello");
    Node* found = find_char(list, 'e');
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->data, 'e');
    Node* not_found = find_char(list, 'x');
    EXPECT_EQ(not_found, nullptr);
    free(list);
}

// Test for the find_list function
TEST(ListTests, FindList) {
    Node* haystack = from_string("hello");
    Node* needle = from_string("ll");
    Node* found = find_list(haystack, needle);
    ASSERT_NE(found, nullptr);
    std::ostringstream found_str;
    print(found_str, found);
    EXPECT_EQ(found_str.str().substr(0, 2), "ll");
    Node* not_found = find_list(haystack, from_string("world"));
    EXPECT_EQ(not_found, nullptr);
    free(haystack);
    free(needle);
}

// Test for the nth function
TEST(ListTests, Nth) {
    Node* list = from_string("hello");
    Node* third = nth(list, 2);
    ASSERT_NE(third, nullptr);
    EXPECT_EQ(third->data, 'l');
    Node* out_of_bounds = nth(list, 5);
    EXPECT_EQ(out_of_bounds, nullptr);
    free(list);
}

// Test for the last function
TEST(ListTests, Last) {
    Node* list = from_string("test");
    Node* last_node = last(list);
    ASSERT_NE(last_node, nullptr);
    EXPECT_EQ(last_node->data, 't');
    free(list);
}