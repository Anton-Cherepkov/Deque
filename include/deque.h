//
// Created by anton on 05.11.16.
//

#ifndef DEQUE_DEQUE_H
#define DEQUE_DEQUE_H

#include <cstdio>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "deque_iterator.h"

template <class T>
class Deque {

private:

    T* buffer = nullptr;

    size_t head;
    size_t tail;
    size_t capacity;

    const size_t DECREASE_CAPACITY_THRESHOLD = 4;
    const size_t CHANGE_CAPACITY_RATIO = 2;
    const size_t INITIAL_CAPACITY = 4;

    void realloc(const size_t& new_capacity) {
        T* temp_buffer = new T[new_capacity];

        size_t old_size = size();
        tail = size();

        for (size_t i = 0; i < old_size; ++i) {
            temp_buffer[i] = buffer[head];
            head = (head + 1) % capacity;
        }

        delete[] buffer;
        buffer = temp_buffer;

        head = 0;

        capacity = new_capacity;
    }

    void try_to_decrease_capacity() {
        if (!(size() < capacity / DECREASE_CAPACITY_THRESHOLD) || capacity < (INITIAL_CAPACITY << 1))
            return;
        realloc(capacity >> CHANGE_CAPACITY_RATIO);
    }

    void try_to_increase_capacity() {
        if (!(head == (tail + 1) % capacity))
            return;
        realloc(capacity << CHANGE_CAPACITY_RATIO);
    }

public:

    // Typedef iterators

    typedef DequeIterator<T, T*, T&> iterator;
    typedef DequeIterator<T, const T*, const T&> const_iterator;
    typedef std::reverse_iterator<DequeIterator<T, T*, T&>> reverse_iterator;
    typedef std::reverse_iterator<DequeIterator<T, const T*, const T&>> const_reverse_iterator;

    // Constructors & destructors

    Deque() {
        capacity = INITIAL_CAPACITY;
        buffer = new T[capacity];
        head = 0;
        tail = 0;
    }

    Deque(const Deque& other) {
        (*this) = other;
    }

    ~Deque() {
        if (buffer != nullptr)
            delete[] buffer;
    }

    Deque& operator =(const Deque& other) {
        if (buffer != nullptr)
            delete[] buffer;
        buffer = new T[other.capacity];
        std::copy(other.buffer, other.buffer + other.capacity, buffer);
        head = other.head;
        tail = other.tail;
        capacity = other.capacity;
        return *this;
    }

    // Element access

    T& at(size_t pos) {
        if (!(pos < size())) {
            throw std::out_of_range("Deque::out of range, pos(" + std::to_string(pos) + ") >= size (" + std::to_string(size()) + ")");
        }
        return (*this)[pos];
    }

    const T& at(size_t pos) const {
        if (!(pos < size())) {
            throw std::out_of_range("Deque::out of range, pos(" + std::to_string(pos) + ") >= size (" + std::to_string(size()) + ")");
        }
        return (*this)[pos];
    }

    T& operator [](size_t pos) {
        return buffer[(head + pos) % capacity];
    }

    const T& operator [](size_t pos) const {
        return buffer[(head + pos) % capacity];
    }

    T& front() {
        return (*this)[0];
    }

    const T& front() const {
        return (*this)[0];
    }

    T& back() {
        return (*this)[size() - 1];
    }

    const T& back() const {
        return (*this)[size() - 1];
    }

    // Capacity

    bool empty() const {
        return !size();
    }

    size_t size() const {
        return head > tail ? capacity + tail - head : tail - head;
    }

    void shink_to_fit() {
        if (size() > INITIAL_CAPACITY && capacity > size() + 1) {
            realloc(size() + 1);
        }
    }

    // Modifiers

    void clear() {
        (*this) = Deque();
    }

    void push_back(const T& elem) {
        try_to_increase_capacity();
        buffer[tail] = elem;
        tail = (tail + 1) % capacity;
    }

    void pop_back() {
        try_to_decrease_capacity();
        tail = (capacity + tail - 1) % capacity;
    }

    void push_front(const T& elem) {
        try_to_increase_capacity();
        head = (capacity + head - 1) % capacity;
        buffer[head] = elem;
    }

    void pop_front() {
        try_to_decrease_capacity();
        head = (head + 1) % capacity;
    }

    // Iterators

    iterator begin() {
        return iterator(buffer, capacity, head, tail, 0);
    }

    const_iterator begin() const {
        return const_iterator(buffer, capacity, head, tail, 0);
    }

    const_iterator cbegin() const {
        return const_iterator(buffer, capacity, head, tail, 0);
    }

    iterator end() {
        return iterator(buffer, capacity, head, tail, size());
    }

    const_iterator end() const {
        return const_iterator(buffer, capacity, head, tail, size());
    }

    const_iterator cend() const {
        return const_iterator(buffer, capacity, head, tail, size());
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(cend());
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(cbegin());
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }
};

#endif //DEQUE_DEQUE_H