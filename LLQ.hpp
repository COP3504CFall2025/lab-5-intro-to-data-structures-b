#pragma once
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list() {}

    // Insertion
    void enqueue(const T& item) override
    {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override
    {
        if(list.getCount() == 0)
        {
            throw std::runtime_error("Linked-List Queue is empty.");
        }

        T returnValue = list.getHead()->data;
        list.removeHead();

        return returnValue;

    }

    // Access
    T peek() const override
    {
        if(list.getCount() == 0)
        {
            throw std::runtime_error("Linked-List Queue is empty.");
        }

        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override
    {
        return list.getCount();
    }

};