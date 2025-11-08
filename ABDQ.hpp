#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    //Constructors
    ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0) {}
    explicit ABDQ(std::size_t capacity) : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {}

    //copy constructor
    ABDQ(const ABDQ& other) : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.front_)
    {
        for(size_t i = 0; i < other.size_; i++)
        {
            this->data_[i] = other.data_[i];
        }
    }

    //move constructor
    ABDQ(ABDQ&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.front_)
    {
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }

    //copy assignment operator
    ABDQ& operator=(const ABDQ& other)
    {
        if(this == &other)
        {
            return *this;
        }

        delete[] this->data_;
        this->data_ = new T[other.capacity_];

        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        for(size_t i = 0; i < other.size_; i++)
        {
            this->data_[i] = other.data_[i];
        }

        return *this;
    }

    //move assignment operator
    ABDQ& operator=(ABDQ&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] this->data_;

        this->data_ = other.data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;

        return *this;
    }

    //destructor
    ~ABDQ() override
    {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override
    {
        if(capacity_ == size_)
        {
            capacity_ *= SCALE_FACTOR;

            T* temp = new T[capacity_];
            for(size_t i = 0; i < size_; i++)
            {
                temp[i] = data_[(front_ + i) % size_];
            }

            delete[] data_;
            data_ = temp;
            temp = nullptr;
        }

        front_ = (front_ - 1 + capacity_) % capacity_;
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override
    {
        if(capacity_ == size_)
        {
            capacity_ *= SCALE_FACTOR;

            T* temp = new T[capacity_];
            for(size_t i = 0; i < size_; i++)
            {
                temp[i] = data_[(front_ + i) % size_];
            }

            delete[] data_;
            data_ = temp;
            temp = nullptr;
        }

        data_[back_] = item;
        back_ = (back_ - 1 + capacity_) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override
    {
        if(size_ == 0)
        {
            throw std::runtime_error("Array-Based Deque is empty.");
        }

        T returnValue = data_[front_];

        front_ = (front_ + 1 + capacity_) % capacity_;

        return returnValue;
    }
    T popBack() override
    {
        if(size_ == 0)
        {
            throw std::runtime_error("Array-Based Deque is empty.");
        }

        T returnValue = data_[(back_ - 1 + capacity_) % capacity_];

        back_ = (front_ - 1 + capacity_) % capacity_;

        return returnValue;
    }

    // Access
    const T& front() const override
    {
        if(size_ == 0)
        {
            throw std::runtime_error("Array-Based Deque is empty.");
        }

        return data_[front_];
    }
    const T& back() const override
    {
        if(size_ == 0)
        {
            throw std::runtime_error("Array-Based Deque is empty.");
        }

        return data_[(back_ - 1 + capacity_) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override
    {
        return size_;
    }

};
