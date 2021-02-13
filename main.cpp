/**
 * This is the first homework for DSA course in Innopolis University.
 *
 * Author - Sinii Viacheslav
 */

#include <iostream>

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

template <typename T>
class SortedList
{
    virtual void add(T item) = 0;
    virtual T least() = 0;
    virtual T greatest() = 0;
    virtual T get(int i) = 0;
    virtual int indexOf(T item) = 0;
    virtual void remove(int i) = 0;
    virtual SortedList<T> searchRange(T from, T to) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

template <typename T>
class LinkedSortedList : SortedList<T>
{
public:
    LinkedSortedList()
    {
        struct Node initial = { NULL, nullptr };
        first = &initial;
        last = &initial;
    }

    void add(T item)
    {
        if (first->data == NULL)
        {
            first->data = item;
        }

        struct Node *currentNode = first;
        while (currentNode->next != nullptr && item > currentNode->next->data)
        {
            currentNode = currentNode->next;
        }

        struct Node newNode = { item, currentNode->next };
        currentNode->next = &newNode;

        if (newNode.next == nullptr)
        {
            last = &newNode;
        }
    }

    T least()
    {
        return first->data;
    }

    T greatest()
    {
        return last->data;
    }

    T get(int i)
    {

    }

    int indexOf(T item)
    {

    }

    void remove(int i)
    {

    }

    LinkedSortedList<T> searchRange(T from, T to)
    {

    }

    int size()
    {
        return listSize;
    }

    bool isEmpty()
    {
        return listSize == 0;
    }
private:
    struct Node
    {
        T data;
        struct Node* next;
    };

    struct Node* first;
    struct Node* last;
    unsigned int listSize = 0;
};
