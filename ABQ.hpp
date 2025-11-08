#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}
    explicit ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity_]) {}
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override
    {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept
    {
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept
    {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override
    {
        if(capacity_ == curr_size_)
        {
            capacity_ *= scale_factor_;

            T* temp = new T[capacity_];
            for(size_t i = 0; i < curr_size_; i++)
            {
                temp[i] = array_[i];
            }

            delete[] array_;
            array_ = temp;
            temp = nullptr;

            array_[curr_size_] = data;
            curr_size_++;
        }
        else
        {
            array_[curr_size_] = data;
            curr_size_++;
        }
    }

    // Access
    T peek() const override
    {
        if(curr_size_ == 0)
        {
            throw std::runtime_error("Array-Based Stack is empty.");
        }

        return array_[0];
    }

    // Deletion
    T dequeue() override
    {
        if (curr_size_ == 0)
        {
            throw std::runtime_error("Array-Based Stack is empty.");
        }
        else
        {
            T returnValue = array_[0];
            curr_size_--;

            if(curr_size_ <= capacity_/4)
            {
                capacity_ /= 2;
                if(capacity_ < 1)
                {
                    capacity_ = 1;
                }

                T* temp = new T[capacity_];
                for(size_t i = 1; i < curr_size_; i++)
                {
                    temp[i - 1] = array_[i];
                }

                delete[] array_;
                array_ = temp;
                temp = nullptr;

                return returnValue;
            }

            T* temp = new T[capacity_];
            for(size_t i = 1; i < curr_size_; i++)
            {
                temp[i - 1] = array_[i];
            }

            delete[] array_;
            array_ = temp;
            temp = nullptr;

            return array_[0];
        }
    }

};
