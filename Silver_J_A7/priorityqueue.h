#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <iostream>

// structure for an edge in a graph
struct t {
    int u, v;
    double w;
    t(int u, int v, double w) :u{u}, v{v}, w{w} {}
    t() = default;
    bool operator<(const t &rhs)const {
        return w < rhs.w;
    }
};

class PriorityQueue {
public:
    PriorityQueue(int size)
        : m_elements(nullptr), num_elements(0), capacity(size) {
        m_elements = new t[size];
    }

    ~PriorityQueue() {
        delete [] m_elements;
    }

    bool empty() const {
        return !num_elements;
    }

    // add an item to the queue
    void put(t item) {
        if (num_elements == capacity) {
            throw std::runtime_error("Queue is full!");
        }
        m_elements[num_elements] = item;
        ++num_elements;
    }

    // get the lowest priority item
    t get() {
        // find the index of the lowest priority item
        double lowest_priority = priority_func(m_elements[0]);
        int lowest_priority_index = 0;
        for (int i = 1; i < num_elements; ++i) {
            double priority = priority_func(m_elements[i]);
            if (priority < lowest_priority) {
                lowest_priority = priority;
                lowest_priority_index = i;
            }
        }

        // remove the lowest priority item from the queue
        t lowest_priority_item = m_elements[lowest_priority_index];
        for (int i = lowest_priority_index; i < num_elements - 1; ++i) {
            m_elements[i] = m_elements[i + 1];
        }
        --num_elements;

        return lowest_priority_item;
    }

private:
    t* m_elements;
    int num_elements;
    int capacity;
    double priority_func(const t &t) { return t.w;}  //target
};

#endif // PRIORITYQUEUE_H
