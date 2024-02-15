#include "list.hpp"
#include <iostream>
#include <cstring>

namespace list {

    Node *from_string(const char *s) {
        if (!s || *s == '\0') return nullptr;
        Node *head = new Node{*s++, nullptr};
        Node *current = head;
        while (*s) {
            current->next = new Node{*s++, nullptr};
            current = current->next;
        }
        return head;
    }

    void free(Node* head) {
        while (head != nullptr) {
            Node* temp = head->next;
            delete head;
            head = temp;
        }
    }

    void print(std::ostream &out, Node *head) {
        for (Node *current = head; current != nullptr; current = current->next) {
            out << current->data;
        }
    }

    Node* copy(Node* head) {
        if (head == nullptr) return nullptr;

        Node dummy = {0, nullptr};
        Node* tail = &dummy;

        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            tail->next = new Node{curr->data, nullptr};
            tail = tail->next;
        }
        return dummy.next;
    }

    int compare(Node *lhs, Node *rhs) {
        while (lhs && rhs && lhs->data == rhs->data) {
            lhs = lhs->next;
            rhs = rhs->next;
        }
        if (!lhs && !rhs) return 0;  // Both lists are the same
        if (!lhs) return -1;         // lhs is shorter than rhs
        if (!rhs) return 1;          // rhs is shorter than lhs
        return lhs->data - rhs->data;
    }

    int compare(Node* lhs, Node* rhs, int n) {
        int index = 0;
        while (lhs != nullptr && rhs != nullptr && index < n) {
            if (lhs->data != rhs->data) {
                return lhs->data - rhs->data;
            }
            lhs = lhs->next;
            rhs = rhs->next;
            ++index;
        }

        if (index == n) return 0;
        if (lhs == nullptr && rhs == nullptr) return 0;
        if (lhs == nullptr) return -1;
        if (rhs == nullptr) return 1;

        return 0;
    }

    int length(Node *head) {
        int len = 0;
        while (head) {
            ++len;
            head = head->next;
        }
        return len;
    }

    Node* reverse(Node* head) {
        Node* new_head = nullptr;
        while (head != nullptr) {
            // Allocate a new node with the same data as the current node
            Node* node = new Node;
            node->data = head->data;

            // Insert the new node at the beginning of the new list
            node->next = new_head;
            new_head = node;

            // Move to the next node in the original list
            head = head->next;
        }
        return new_head;
    }

    Node *append(Node *lhs, Node *rhs) {
        if (!lhs) return copy(rhs);

        Node *new_list = copy(lhs);
        Node *current = new_list;
        while (current->next) current = current->next;
        current->next = copy(rhs);

        return new_list;
    }

    int index(Node *head, Node *node) {
        int idx = 0;
        while (head && head != node) {
            head = head->next;
            ++idx;
        }
        return head ? idx : -1;
    }

    Node *find_char(Node *head, char c) {
        while (head && head->data != c) head = head->next;
        return head;
    }

    Node *find_list(Node *haystack, Node *needle) {
        if (!needle) return haystack;  // Finding empty list in any list returns the list itself
        Node *start = haystack;
        while (start) {
            Node *current_haystack = start;
            Node *current_needle = needle;
            while (current_haystack && current_needle && current_haystack->data == current_needle->data) {
                current_haystack = current_haystack->next;
                current_needle = current_needle->next;
            }
            if (!current_needle) return start;  // Found the whole needle in haystack
            start = start->next;
        }
        return nullptr;  // Needle not found
    }

    Node *nth(Node *head, int n) {
        while (n-- > 0 && head) head = head->next;
        return head;
    }

    Node* last(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        while (head->next != nullptr) {
            head = head->next;
        }
        return head;
    }

};