#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : curr_size_(0), capacity_(1), array_(new T[capacity_]) {}
    explicit ABS(const size_t capacity) : curr_size_(0), capacity_(capacity), array_(new T[capacity_]) {}
    //copy constructor
    ABS(const ABS& other) : curr_size_(other.curr_size_), capacity_(other.capacity_), array_(new T[other.capacity_])
    {
        for(size_t i = 0; i < other.curr_size_; i++)
        {
            array_[i] = other.array_[i];
        }
    }
    //copy assignment operator
    ABS& operator=(const ABS& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }

        delete[] this->array_;
        this->array_ = new T[rhs.capacity_];

        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;

        for(size_t i = 0; i < rhs.curr_size_; i++)
        {
            array_[i] = rhs.array_[i];
        }

        return *this;
    }
    //move constructor
    ABS(ABS&& other) noexcept : curr_size_(other.curr_size_), capacity_(other.capacity_), array_(other.array_)
    {
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    //move assignment operator
    ABS& operator=(ABS&& rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this;
        }

        delete[] this->array_;

        this->array_ = rhs.array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;

        return *this;
    }
    ~ABS() noexcept override
    {
        capacity_ = 0;
        curr_size_ = 0;
        delete[] array_;
        array_ = nullptr;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override
    {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept
    {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept
    {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override
    {
        if(capacity_ == curr_size_)
        {
            capacity_ *= scale_factor_;

            T* temp = new T[capacity_];
            for(size_t i = 0; i < curr_size_; i++)
            {
                temp[i] = array_[i];
            }

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

    T peek() const override
    {
        return array_[curr_size_ - 1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Array-Based Stack is empty.");
        }
        else
        {
            curr_size_--;
            return array_[curr_size_];
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
