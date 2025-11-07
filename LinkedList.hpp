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
        for(int i = 0; i < count; i++)
        {
            std::cout << *current << std::endl;
            current = current->next;
        }
    }
	void printReverse() const
    {
        Node<T>* current = tail;
        for(int i = 0; i < count; i++)
        {
            std::cout << *current << std::endl;
            current = current->next;
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
	void addHead(const T& data)
    {
        Node<T>* temp = new Node<T>(data);
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
    }
	void addTail(const T& data)
    {
        Node<T>* temp = new Node<T>(data);
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
    }

	// Removal
	bool removeHead()
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
            return 1;
        }

        Node<T>* temp = head->next;
        delete head;
        head = temp;

        return 1;
    }
	bool removeTail()
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
            return 1;
        }

        Node<T>* temp = tail->prev;
        delete tail;
        tail = temp;

        return 1;

    }
	void Clear()
    {
        Node<T>* current = head;
        Node<T>* next;
        for(int i = 0; i < count; i++)
        {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }

	// Move/Copy Assignment Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept
    {
        if(this == other)
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

        this->count = rhs.count;
        this->head = new Node<T>;
        Node<T>* current = rhs.head;
        for(int i = 0; i < this->count; i++)
        {
            addTail(current->data);
        }

        return *this;
    }

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(list.count)
    {
        this->head = new Node<T>;
        Node<T>* current = list.head;
        for(int i = 0; i < this->count; i++)
        {
            addTail(current->data);
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