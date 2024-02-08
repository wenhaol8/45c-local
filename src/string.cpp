#include "string.hpp"
#include <cstring> // For strlen, strcpy, etc.
#include <algorithm> // For std::swap
#include <iostream> // For std::ostream, std::istream

// Helper function to safely allocate and copy strings
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
String& String::operator=(String s) {
    swap(s);
    return *this;
}


// Swap Method
void String::swap(String& s) {
    std::swap(buf, s.buf);
}

// Size Method
int String::size() const {
    return std::strlen(buf);
}

// Index Operator
char& String::operator[](int index) {
    return buf[index]; // Add bounds checking in real implementation
}

// Const Index Operator
const char& String::operator[](int index) const {
    return buf[index]; // Add bounds checking in real implementation
}

// Concatenation Operator
String String::operator+(const String& s) const {
    String result;
    int newSize = size() + s.size(); // Plus null terminator
    result.buf = new char[newSize + 1];
    std::strcpy(result.buf, buf);
    std::strcat(result.buf, s.buf);
    return result;
}

// Concatenation and Assignment Operator
String& String::operator+=(const String& s) {
    *this = *this + s; // Leverages operator+
    return *this;
}

// Print Method
void String::print(std::ostream& out) const {
    out << this->buf;

}

// Read Method
void String::read(std::istream& in) {
    std::string temp; // Use std::string for convenience
    std::getline(in, temp); // Read the entire line

    // Now, allocate or reallocate the buffer to fit the new data
    delete[] this->buf; // Free the existing buffer
    this->buf = new char[temp.length() + 1]; // Allocate new buffer
    std::strcpy(this->buf, temp.c_str()); // Copy data into the new buffer
}

String String::reverse() const {
    int len = size();
    char* reversed = new char[len + 1];
    for (int i = 0; i < len; ++i) {
        reversed[i] = buf[len - 1 - i];
    }
    reversed[len] = '\0';
    String reversedString(reversed);
    delete[] reversed; // Clean up the temporary buffer
    return reversedString;
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
    const char *sc;
    for (sc = s; *sc != '\0'; ++sc) { }
    return sc - s;
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
    for ( ; n > 0; left++, right++, n--) {
        if (*left != *right) {
            return *(unsigned char *)left - *(unsigned char *)right;
        } else if (*left == '\0') {
            return 0;
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
    if (!needle || !*needle) {
        return haystack;
    }

    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;

        while (*h && *n && *h == *n) {
            ++h;
            ++n;
        }

        if (!*n) {
            return haystack;
        }
        ++haystack;
    }
    return nullptr;
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