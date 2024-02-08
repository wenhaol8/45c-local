#include "string.hpp"
#include <cstring>
#include <iostream>
#include <sstream>

char* allocate_and_copy(const char* src) {
    if (src == nullptr) {
        return nullptr;
    }
    char* dest = new char[std::strlen(src) + 1];
    std::strcpy(dest, src);
    return dest;
}

// Default Constructor & Constructor from C-String
String::String(const char* s)
        : buf(allocate_and_copy(s)) {
}

// Copy Constructor
String::String(const String& s)
        : buf(allocate_and_copy(s.buf)) {
}

// Destructor
String::~String() {
    delete[] buf;
}

// Copy Assignment Operator using Copy-and-Swap Idiom
String& String::operator=(const String &s) {
    if (this != &s) {
        String temp(s);
        swap(temp);
    }
    return *this;
}


String& String::operator=(String &&s) noexcept {
    if (this != &s) {
        delete[] buf;
        buf = s.buf;
        s.buf = nullptr;
    }
    return *this;
}

// Swap Method
void String::swap(String& s) {
    std::swap(buf, s.buf);
}

// Size Method
int String::size() const {
    return strlen(buf);
}

// Index Operator
char &String::operator[](int index) {
    if (!in_bounds(index)) {
        std::cout << "ERROR" << std::endl;
        static char dummy = '\0';
        return dummy;
    }
    return buf[index];
}


const char &String::operator[](int index) const {
    if (!in_bounds(index)) {
        std::cout << "ERROR" << std::endl;
        static const char dummy = '\0';
        return dummy;
    }
    return buf[index];
}

String String::operator+(const String& s) const {
    int newSize = size() + s.size();
    String result(newSize + 1);
    std::strcpy(result.buf, buf);
    std::strcat(result.buf, s.buf);
    return result;
}

// Optimized operator+=
String& String::operator+=(const String& s) {
    int newSize = size() + s.size();
    char* newBuf = new char[newSize + 1];
    std::strcpy(newBuf, buf);
    std::strcat(newBuf, s.buf);
    delete[] buf;
    buf = newBuf;
    return *this;
}


void String::print(std::ostream& out) const {
    out << this->buf;

}

void String::read(std::istream& in) {
    std::string line;
    std::getline(in, line);
    std::istringstream iss(line);

    std::string word;
    if (iss >> word) {
        delete[] buf;
        buf = new char[word.length() + 1];
        std::strcpy(buf, word.c_str());
    }
}

String String::reverse() const {
    int len = size();
    String result(len + 1);
    for (int i = 0; i < len; ++i) {
        result.buf[i] = buf[len - i - 1];
    }
    result.buf[len] = '\0';
    return result;
}

int String::indexOf(char c) const {
    for (int i = 0; buf[i] != '\0'; ++i) {
        if (buf[i] == c) {
            return i;
        }
    }
    return -1; // Character not found
}

int String::indexOf(const String& s) const {
    int thisLen = size();
    int sLen = s.size();
    if (sLen > thisLen) return -1; // Substring longer than string

    for (int i = 0; i <= thisLen - sLen; ++i) {
        bool match = true;
        for (int j = 0; j < sLen; ++j) {
            if (buf[i + j] != s.buf[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }
    return -1; // Substring not found
}


bool String::operator==(const String& s) const {
    return strcmp(buf, s.buf) == 0;
}

// Inequality operator
bool String::operator!=(const String& s) const {
    return strcmp(buf, s.buf) != 0;
}

// Less than operator
bool String::operator<(const String& s) const {
    return strcmp(buf, s.buf) < 0;
}

// Greater than operator
bool String::operator>(const String& s) const {
    return strcmp(buf, s.buf) > 0;
}

// Less than or equal to operator
bool String::operator<=(const String& s) const {
    return strcmp(buf, s.buf) <= 0;
}

// Greater than or equal to operator
bool String::operator>=(const String& s) const {
    return strcmp(buf, s.buf) >= 0;
}



int String::strlen(const char *s) {
    int length = 0;
    while (s[length] != '\0') {
        ++length;
    }
    return length;
}

char *String::strcpy(char *dest, const char *src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }

    dest[i] = '\0';

    return dest;
}


// Copies a C-string into another, with the destination size limited
char *String::strncpy(char *dest, const char *src, int n) {
    int i=0;

    for ( ; src[i] != '\0' && i < n; ++i )

        dest[i] = src[i];

    dest[i] = '\0';

    return dest;
}


char *String::strcat(char *dest, const char *src) {
    int i = 0;
    while (dest[i] != '\0') {
        ++i;
    }

    int j = 0;
    while (src[j] != '\0') {
        dest[i + j] = src[j];
        ++j;
    }

    dest[i + j] = '\0';

    return dest;
}

// Appends a C-string to another, with destination size limited
char *String::strncat(char *dest, const char *src, int n) {
    if (dest == nullptr || src == nullptr || n <= 0) {
        return dest; // handle invalid input
    }

    char *temp = dest;

    // Move to the end of dest
    while (*dest) {
        dest++;
    }

    // Keep track of the number of characters written
    int written = 0;

    // Copy characters from src to dest, checking for dest's limit
    while (written < n && *src != '\0') {
        *dest++ = *src++;
        written++;
    }

    *dest = '\0';

    return temp;
}


int String::strcmp(const char *left, const char *right) {
    int i = 0;
    while (left[i] != '\0' && right[i] != '\0') {
        if (left[i] != right[i]) {
            return left[i] - right[i];
        }
        ++i;
    }

    return left[i] - right[i];
}


int String::strncmp(const char *left, const char *right, int n) {
    if (n == 0) {
        return 0;
    }

    for (; n > 0; left++, right++, n--) {
        if (*left == '\0' || *right == '\0') {
            return *left == '\0' && *right == '\0' ? 0 : (*left == '\0' ? -1 : 1);
        }
        if (*left != *right) {
            return *(unsigned char *)left - *(unsigned char *)right;
        }
    }
    return 0;
}


void String::reverse_cpy(char *dest, const char *src) {
    int len = strlen(src);
    for (int i = 0; i < len; ++i) {
        dest[i] = src[len - i - 1];
    }
    dest[len] = '\0';
}


const char *String::strchr(const char *str, char c) {
    while (*str != c) {
        if (!*str++) {
            return nullptr;
        }
    }
    return str;
}

const char *String::strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return haystack;
    }

    int len = strlen(needle);
    for (const char *p = haystack; (p = strchr(p, needle[0])); ++p) {
        if (strncmp(p, needle, len) == 0) {
            return p;
        }
    }

    return nullptr;
}

char *String::strdup(const char *src) {
    if (src == nullptr) {
        return nullptr; // Handle null input string
    }

    // Calculate length of src plus one for the null terminator
    int len = String::strlen(src) + 1;

    // Allocate memory for duplicate
    char *dup = new char[len];

    // Copy string into allocated memory
    for (int i = 0; i < len; ++i) {
        dup[i] = src[i];
    }

    // Return the pointer to the duplicate
    return dup;
}

String::String(String &&s)  noexcept : buf(s.buf) {
    s.buf = nullptr; // Leave source in a valid state
}

String::String(int length) : buf(new char[length]) {
    std::fill_n(buf, length, '\0');
}




std::ostream &operator<<(std::ostream &out,const String& s) {
    s.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, String& s) {
    // Assuming a suitable read function exists
    s.read(in);
    return in;
}