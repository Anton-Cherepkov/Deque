//
// Created by anton on 05.11.16.
//

#ifndef DEQUE_DEQUE_H
#define DEQUE_DEQUE_H

#include <cstdio>

template <class T>
class Deque {

private:

    T* buffer;

    size_t tail;
    size_t head;
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

    Deque() {
        buffer = new T[INITIAL_CAPACITY];
        capacity = INITIAL_CAPACITY;
        head = 0;
        tail = 0;
    }

    ~Deque() {
        delete[] buffer;
    }

    size_t size() const {
        return head > tail ? capacity + tail - head : tail - head;
    }

    bool empty() const {
        return !size();
    }

    void pop_back() {
        try_to_decrease_capacity();
        tail = (capacity + tail - 1) % capacity;
    }

    void pop_front() {
        try_to_decrease_capacity();
        head = (head + 1) % capacity;
    }

    void push_back(const T& elem) {
        try_to_increase_capacity();
        buffer[tail] = elem;
        tail = (tail + 1) % capacity;
    }

    void push_front(const T& elem) {
        try_to_increase_capacity();
        head = (capacity + head - 1) % capacity;
        buffer[head] = elem;
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

};

#endif //DEQUE_DEQUE_H