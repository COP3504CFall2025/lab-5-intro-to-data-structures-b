#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
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
        Node<T>* temp = new Node<T>;
        *temp->data = data;
        *temp->next = head;
        head = temp;
    }
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void Clear();

	// Move/Copy Assignment Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};