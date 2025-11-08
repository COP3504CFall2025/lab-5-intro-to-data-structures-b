#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template <typename T>
class LinkedList
{
public:
	// Behaviors
	void printForward() const
    {
        Node<T>* current = head;
        for(size_t i = 0; i < count; i++)
        {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
	void PrintReverse() const
    {
        Node<T>* current = tail;
        for(size_t i = 0; i < count; i++)
        {
            std::cout << current->data << std::endl;
            current = current->prev;
        }
    }

	// Accessors
	[[nodiscard]] unsigned int getCount() const
    {
        return count;
    }
	Node<T>* getHead()
    {
        return head;
    }
	const Node<T>* getHead() const
    {
        return head;
    }
	Node<T>* getTail()
    {
        return tail;
    }
	const Node<T>* getTail() const
    {
        return tail;
    }

	// Insertion
	void AddHead(const T& data)
    {
        Node<T>* temp = new Node<T>;
        temp->data = data;
        temp->prev = nullptr;
        if(count == 0)
        {
            tail = temp;
            temp->next = nullptr;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
        }
        head = temp;
        count++;
    }
	void AddTail(const T& data)
    {
        Node<T>* temp = new Node<T>;
        temp->data = data;
        temp->next = nullptr;
        if(count == 0)
        {
            head = temp;
            temp->prev = nullptr;
        }
        else
        {
            temp->prev = tail;
            tail->next = temp;
        }
        tail = temp;
        count++;
    }

	// Removal
	bool RemoveHead()
    {
        if(count == 0)
        {
            return 0;
        }

        if(count == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            count--;
            return 1;
        }

        Node<T>* temp = head->next;
        delete head;
        head = temp;
        head->prev = nullptr;
        count--;

        return 1;
    }
	bool RemoveTail()
    {
        if(count == 0)
        {
            return 0;
        }

        if(count == 1)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
            count--;
            return 1;
        }

        Node<T>* temp = tail->prev;
        delete tail;
        tail = temp;
        tail->next = nullptr;
        count--;

        return 1;

    }
	void Clear()
    {
        Node<T>* current = head;
        Node<T>* next = nullptr;
        while(current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

	// Move/Copy Assignment Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept
    {
        if(this == &other)
        {
            return *this;
        }

        this->~LinkedList();

        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;

        return *this;
    }
	LinkedList<T>& operator=(const LinkedList<T>& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }

        this->~LinkedList();

        this->count = 0;
        this->head = new Node<T>;
        Node<T>* current = rhs.head;
        for(size_t i = 0; i < rhs.count; i++)
        {
            AddTail(current->data);
            current = current->next;
        }

        return *this;
    }

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(list.count)
    {
        this->head = new Node<T>;
        Node<T>* current = list.head;

        this->count = 0;
        for(size_t i = 0; i < list.count; i++)
        {
            AddTail(current->data);
            current = current->next;
        }
    }
	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }
	~LinkedList()
    {
        Clear();
    }

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};