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

    void free(Node *head) {
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print(std::ostream &out, Node *head) {
        for (Node *current = head; current != nullptr; current = current->next) {
            out << current->data;
        }
    }

    Node *copy(Node *head) {
        if (!head) return nullptr;

        Node *new_head = new Node{head->data, nullptr};
        Node *current_new = new_head;
        Node *current_old = head->next;

        while (current_old) {
            current_new->next = new Node{current_old->data, nullptr};
            current_new = current_new->next;
            current_old = current_old->next;
        }

        return new_head;
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

    int compare(Node *lhs, Node *rhs, int n) {
        for (int i = 0; lhs && rhs && i < n && lhs->data == rhs->data; ++i) {
            lhs = lhs->next;
            rhs = rhs->next;
        }
        if ((!lhs || !rhs) && n > 0) return 0;  // Reached the end of one list before n
        return lhs->data - rhs->data;
    }

    int length(Node *head) {
        int len = 0;
        while (head) {
            ++len;
            head = head->next;
        }
        return len;
    }

    Node *reverse(Node *head) {
        Node *new_head = nullptr;
        while (head) {
            Node *next = head->next;
            head->next = new_head;
            new_head = head;
            head = next;
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