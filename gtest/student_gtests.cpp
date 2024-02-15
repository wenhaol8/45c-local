#include <gtest/gtest.h>

#include "list.hpp"

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

TEST(ListTests, ReplaceMe) {
    Node* const original_head = list::from_string("test");
    Node* reversed_head = list::reverse(original_head);

    const char* reversed_content = "tset";
    for (Node* current = reversed_head; current != nullptr; current = current->next, ++reversed_content) {
        EXPECT_EQ(current->data, *reversed_content);
    }
    EXPECT_EQ(*reversed_content, '\0');

    list::free(original_head);
    list::free(reversed_head);
}

TEST(ListTests, LengthEmpty) {
    Node* const head = list::from_string("");
    EXPECT_EQ(list::length(head), 0);
    list::free(head);
}

// Test the find_char function
TEST(ListTests, FindChar) {
    Node* const head = list::from_string("hello");
    Node* const o_node = list::find_char(head, 'o');
    ASSERT_NE(o_node, nullptr);
    EXPECT_EQ(o_node->data, 'o');
    list::free(head);
}

// Test the compare function for equal lists
TEST(ListTests, CompareEqual) {
    Node* const list1 = list::from_string("test");
    Node* const list2 = list::from_string("test");
    EXPECT_EQ(list::compare(list1, list2), 0);
    list::free(list1);
    list::free(list2);
}

// Test the compare function for unequal lists
TEST(ListTests, CompareUnequal) {
    Node* const list1 = list::from_string("test");
    Node* const list2 = list::from_string("toast");
    EXPECT_NE(list::compare(list1, list2), 0);
    list::free(list1);
    list::free(list2);
}

// Test the nth function
TEST(ListTests, Nth) {
    Node* const head = list::from_string("hello");
    Node* const third_node = list::nth(head, 2);
    ASSERT_NE(third_node, nullptr);
    EXPECT_EQ(third_node->data, 'l');
    list::free(head);
}

// Test the last function
TEST(ListTests, Last) {
    Node* const head = list::from_string("hello");
    Node* const last_node = list::last(head);
    ASSERT_NE(last_node, nullptr);
    EXPECT_EQ(last_node->data, 'o');
    EXPECT_EQ(last_node->next, nullptr);
    list::free(head);
}

// Test appending two lists
TEST(ListTests, Append) {
    Node* const list1 = list::from_string("hello");
    Node* const list2 = list::from_string("world");
    Node* const combined_list = list::append(list1, list2);

    // Check if the combined list is "helloworld"
    const char* combined_content = "helloworld";
    for (Node* current = combined_list; current != nullptr; current = current->next, ++combined_content) {
        EXPECT_EQ(current->data, *combined_content);
    }

    // Should reach the end of the combined string
    EXPECT_EQ(*combined_content, '\0');

    list::free(list1);
    list::free(list2);
    list::free(combined_list);
}

