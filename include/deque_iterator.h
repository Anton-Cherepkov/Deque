//
// Created by anton on 10.11.16.
//

#ifndef DEQUE_DEQUE_ITERATOR_H
#define DEQUE_DEQUE_ITERATOR_H

#include <iterator>

template <class T, class Pointer, class Reference>
class DequeIterator : public std::iterator<std::random_access_iterator_tag, T> {

private:

    T* buffer;
    size_t capacity;
    size_t head;
    size_t tail;

    size_t current;

    size_t position_in_buffer(size_t ind) const {
        return (head + ind) % capacity;
    }

public:

    DequeIterator() {}

    DequeIterator(T* buffer, size_t capacity, size_t head, size_t tail, size_t current) : buffer(buffer), capacity(capacity), head(head), tail(tail), current(current) {}

    DequeIterator(const DequeIterator& other) {
        (*this) = other;
    }

    DequeIterator& operator =(const DequeIterator& other) {
        buffer = other.buffer;
        capacity = other.capacity;
        head = other.head;
        tail = other.tail;
        current = other.current;
        return *this;
    }


    bool operator ==(const DequeIterator& other) const {
        return current == other.current;
    }

    bool operator !=(const DequeIterator& other) const {
        return !(*this == other);
    }

    bool operator <(const DequeIterator& other) const {
        return current < other.current;
    }

    bool operator >(const DequeIterator& other) const {
        return current > other.current;
    }

    bool operator <=(const DequeIterator& other) const {
        return !(*this > other);
    }

    bool operator >=(const DequeIterator& other) const {
        return !(*this < other);
    }


    Reference operator *() {
        return *(buffer + position_in_buffer(current));
    }

    Pointer operator ->() {
        return &**this;
    }


    DequeIterator& operator +=(int shift) {
        current += shift;
        return *this;
    }

    DequeIterator operator +(int shift) const {
        DequeIterator nw(*this);
        nw += shift;
        return nw;
    }

    DequeIterator& operator -=(int shift) {
        current -= shift;
        return *this;
    }

    DequeIterator operator -(int shift) const {
        DequeIterator nw(*this);
        nw -= shift;
        return nw;
    }


    DequeIterator& operator ++() {
        *this += 1;
        return *this;
    }

    DequeIterator operator ++(int) {
        DequeIterator nw(*this);
        ++*this;
        return nw;
    }

    DequeIterator& operator --() {
        *this -= 1;
        return *this;
    }

    DequeIterator operator --(int) {
        DequeIterator nw(*this);
        --*this;
        return nw;
    }


    int operator -(const DequeIterator& other) const {
        return static_cast<int>(current) - static_cast<int>(other.current);
    }

    Pointer operator [](int shift) {
        return *DequeIterator(*this + shift);
    }


};

#endif //DEQUE_DEQUE_ITERATOR_H
