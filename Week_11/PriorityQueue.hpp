#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <iostream>
#include "MinHeap.hpp"
using namespace std;

template <typename T>
class PriorityQueue {
    private:
        MinHeap<T> heap;

    public:
        PriorityQueue() {

        }

        void insert(T& item) {
            heap.insert(item);
        }

        T extractMin() {
            if (isEmpty()) {
                throw std::out_of_range("Priority queue is empty.");
            }
            return heap.extract_min();
        }

        T& peek() {
            return heap.get_min();
        }

        int getSize() {
            return heap.getSize();
        }

        bool isEmpty() {
            return heap.empty();
        }
};

#endif