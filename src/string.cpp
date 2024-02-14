#include "string.hpp"
#include <iostream>
#include <utility>
#include <istream>
#include <ostream>
#include <string>

String::String(const char* s) {
    head = list::from_string(s);
}

String::String(const String& s) {
    head = list::copy(s.head);
}

String::String(String&& s) : head(s.head) {
    s.head = nullptr;
}

String::~String() {
    list::free(head);
}

void String::swap(String& s) {
    std::swap(head, s.head);
}

String& String::operator=(const String& s) {
    if (this != &s) {
        list::free(head);
        head = list::copy(s.head);
    }
    return *this;
}

String& String::operator=(String&& s) {
    if (this != &s) {
        list::free(head);
        head = s.head;
        s.head = nullptr;
    }
    return *this;
}

bool String::in_bounds(int index) const {
    return index >= 0 && index < size();
}

char String::operator[](int index) const {
    list::Node* node = list::nth(head, index);
    return node ? node->data : '\0';
}

int String::size() const {
    return list::length(head);
}

String String::reverse() const {
    list::Node* reversed_head = list::reverse(head);
    String reversed_string(reversed_head);
    list::free(reversed_head);
    return reversed_string;
}

int String::indexOf(char c) const {
    list::Node* node = list::find_char(head, c);
    return list::index(head, node);
}

int String::indexOf(const String& s) const {
    list::Node* node = list::find_list(head, s.head);
    return list::index(head, node);
}

bool String::operator==(const String& s) const {
    return list::compare(head, s.head) == 0;
}

std::strong_ordering String::operator<=>(const String& s) const {
    int result = list::compare(head, s.head);
    if (result == 0) return std::strong_ordering::equal;
    return result < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
}

String String::operator+(const String& s) const {
    list::Node* concatenated_head = list::append(head, s.head);
    String concatenated_string(concatenated_head);
    list::free(concatenated_head);
    return concatenated_string;
}

String& String::operator+=(const String& s) {
    list::Node* concatenated_head = list::append(head, s.head);
    list::free(head);
    head = concatenated_head;
    return *this;
}

void String::print(std::ostream& out) const {
    list::print(out, head);
}

void String::read(std::istream& in) {
    std::string temp;
    in >> temp;
    list::free(head);
    head = list::from_string(temp.c_str());
}

// Private constructor
String::String(list::Node* node_head) : head(node_head) {}

std::ostream& operator<<(std::ostream& out, const String& s) {
    s.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, String& s) {
    s.read(in);
    return in;
}