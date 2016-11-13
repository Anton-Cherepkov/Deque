//
// Created by anton on 05.11.16.
//

#ifndef DEQUE_DEQUE_H
#define DEQUE_DEQUE_H

#include <stdexcept>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "deque_iterator.h"

template <class T>
class Deque {

private:

    T* _buffer = nullptr;

    size_t _head;
    size_t _tail;
    size_t _capacity;
    size_t _size;

    const size_t DECREASE_CAPACITY_THRESHOLD = 4;
    const size_t CHANGE_CAPACITY_RATIO = 2;
    const size_t INITIAL_CAPACITY = 4;

    inline void realloc(const size_t& new_capacity) {
        T* temp_buffer = new T[new_capacity];

        size_t old_size = size();
        _tail = size();

        for (size_t i = 0; i < old_size; ++i) {
            temp_buffer[i] = _buffer[_head];
            move_border_forward(_head);
        }

        delete[] _buffer;
        _buffer = temp_buffer;

        _head = 0;

        _capacity = new_capacity;
    }

    inline void try_to_decrease_capacity() {
        if (!(size() < _capacity / DECREASE_CAPACITY_THRESHOLD) || _capacity < (INITIAL_CAPACITY << 1))
            return;
        realloc(_capacity >> CHANGE_CAPACITY_RATIO);
    }

    inline void try_to_increase_capacity() {
        if (!(_head == (_tail + 1) % _capacity))
            return;
        realloc(_capacity << CHANGE_CAPACITY_RATIO);
    }

    inline void move_border_forward(size_t& val) const {
        ++val;
        if (val == _capacity)
            val = 0;
    }

    inline void move_border_back(size_t& val) const {
        if (val == 0)
            val = _capacity - 1;
        else
            --val;
    }

public:

    // Typedef iterators

    typedef DequeIterator<T, T*, T&> iterator;
    typedef DequeIterator<const T, const T*, const T&> const_iterator;
    typedef std::reverse_iterator<DequeIterator<T, T*, T&>> reverse_iterator;
    typedef std::reverse_iterator<DequeIterator<const T, const T*, const T&>> const_reverse_iterator;

    // Constructors & destructors

    Deque() {
        _capacity = INITIAL_CAPACITY;
        _buffer = new T[_capacity];
        _head = 0;
        _tail = 0;
        _size = 0;
    }

    Deque(const Deque& other) {
        (*this) = other;
    }

    ~Deque() {
        if (_buffer != nullptr)
            delete[] _buffer;
    }

    Deque& operator =(const Deque& other) {
        if (_buffer != nullptr)
            delete[] _buffer;
        if (other._buffer == nullptr) {
            *this = Deque();
            return *this;
        }
        _buffer = new T[other._capacity];
        std::copy(other._buffer, other._buffer + other._capacity, _buffer);
        _head = other._head;
        _tail = other._tail;
        _capacity = other._capacity;
        _size = other._size;
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
        return _buffer[(_head + pos) % _capacity];
    }

    const T& operator [](size_t pos) const {
        return _buffer[(_head + pos) % _capacity];
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
        return _size;
    }

    void shrink_to_fit() {
        if (size() > INITIAL_CAPACITY && _capacity > size() + 1) {
            realloc(size() + 1);
        }
    }

    // Modifiers

    void clear() {
        (*this) = Deque();
    }

    void push_back(const T& elem) {
        try_to_increase_capacity();
        _buffer[_tail] = elem;
        ++_size;
        move_border_forward(_tail);
    }

    void pop_back() {
        try_to_decrease_capacity();
        --_size;
        move_border_back(_tail);
    }

    void push_front(const T& elem) {
        try_to_increase_capacity();
        move_border_back(_head);
        ++_size;
        _buffer[_head] = elem;
    }

    void pop_front() {
        try_to_decrease_capacity();
        --_size;
        move_border_forward(_head);
    }

    // Iterators

    iterator begin() {
        return iterator(_buffer, _capacity, _head, _tail, 0);
    }

    const_iterator begin() const {
        return const_iterator(_buffer, _capacity, _head, _tail, 0);
    }

    const_iterator cbegin() const {
        return const_iterator(_buffer, _capacity, _head, _tail, 0);
    }

    iterator end() {
        return iterator(_buffer, _capacity, _head, _tail, size());
    }

    const_iterator end() const {
        return const_iterator(_buffer, _capacity, _head, _tail, size());
    }

    const_iterator cend() const {
        return const_iterator(_buffer, _capacity, _head, _tail, size());
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