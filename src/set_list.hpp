#ifndef SET_LIST_HPP
#define SET_LIST_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class SetList {
    struct ListNode{
        T data;
        std::shared_ptr<ListNode> next;
    };
public:
    class ListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr) : ptr(ptr) {}

        ListIterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator temp = *this;
            ++(*this);
            return temp;
        }

        reference operator*() const {
            return ptr->data;
        }

        pointer operator->() const {
            return &ptr->data;
        }

        bool operator==(const ListIterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const ListIterator& other) const {
            return !(*this == other);
        }


    private:
        std::shared_ptr<ListNode> ptr;
    };
    using value_type = T;
    using iterator = ListIterator;

    SetList() = default;

    template <std::ranges::input_range Rng>
    explicit SetList(Rng&& rng) {
        std::ranges::for_each(std::forward<Rng>(rng), [this](const auto& value) { this->insert(value); });
    }

    ListIterator begin() {
        return ListIterator(head);
    }

    ListIterator end() {
        return ListIterator();
    }

    bool contains(const T& value) {
        for (auto node = head; node; node = node->next) {
            if (node->data == value) return true;
        }
        return false;
    }

    ListIterator insert(T value) {
        if (!contains(value)) {
            auto newNode = std::make_shared<ListNode>(ListNode{value, head});
            head = newNode;
        }
        return begin();
    }

private:
    std::shared_ptr<ListNode> head = nullptr;
};

#endif