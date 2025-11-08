#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() : list() {}

    // Insertion
    void push(const T& item) override
    {
        list.addHead(item);
    }

    // Deletion
    T pop() override
    {
        if(list.getCount() == 0)
        {
            throw std::runtime_error("Linked-List Stack is empty.");
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
            throw std::runtime_error("Linked-List Stack is empty.");
        }

        return list.getHead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override
    {
        return list.getCount();
    }
};