#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

template <typename Key, typename Value>
class MapArray{
public:
    class ArrayIterator{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ArrayIterator(pointer ptr = nullptr) : ptr(ptr) {}

        ArrayIterator& operator++() {
            ++ptr;
            return *this;
        }

        ArrayIterator operator++(int) {
            ArrayIterator temp = *this;
            ++(*this);
            return temp;
        }

        ArrayIterator& operator--() {
            --ptr;
            return *this;
        }

        ArrayIterator operator--(int) {
            ArrayIterator temp = *this;
            --(*this);
            return temp;
        }

        ArrayIterator& operator+=(difference_type d) {
            ptr += d;
            return *this;
        }

        ArrayIterator& operator-=(difference_type d) {
            ptr -= d;
            return *this;
        }
        friend ArrayIterator operator+(ArrayIterator it, difference_type d) {
            return ArrayIterator(it.ptr + d);
        }

        friend ArrayIterator operator+(difference_type d, ArrayIterator it) {
            return ArrayIterator(it.ptr + d);
        }

        friend ArrayIterator operator-(ArrayIterator it, difference_type d) {
            return ArrayIterator(it.ptr - d);
        }

        friend difference_type operator-(const ArrayIterator& lhs, const ArrayIterator& rhs) {
            return lhs.ptr - rhs.ptr;
        }

        auto operator<=>(const ArrayIterator& other) const = default;

        reference operator*() const {
            return *ptr;
        }

        pointer operator->() const {
            return ptr;
        }

        reference operator[](difference_type d) const {
            return *(ptr + d);
        }

    private:
        std::pair<Key, Value>* ptr;
    };

    using value_type = std::pair<Key, Value>;
    using iterator = ArrayIterator;

    ArrayIterator begin() {
        return ArrayIterator(data.data());
    }

    ArrayIterator end() {
        return ArrayIterator(data.data() + data.size());
    }
    Value& operator[](const Key& key) {
        auto it = std::lower_bound(data.begin(), data.end(), key,
                                   [](const std::pair<Key, Value>& a, const Key& b) {
                                       return a.first < b;
                                   });

        if (it == data.end() || it->first != key) {
            // If the key is not found, insert a new pair at the correct position
            it = data.insert(it, std::make_pair(key, Value{}));
        }

        return it->second;
    }

private:
    std::vector<std::pair<Key,Value>> data;
};




#endif