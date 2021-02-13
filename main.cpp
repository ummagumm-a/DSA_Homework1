/**
 * This is the first homework for DSA course in Innopolis University.
 *
 * Author - Sinii Viacheslav
 */

#include <iostream>
#include <exception>

using namespace std;

namespace exceptions
{
    class IndexOutOfBoundsException : public exception
    {
        virtual const char* what() const throw()
        {
            return "Index out of bounds!";
        }
    };
}

template <typename T>
class List {};

template <typename T>
class SortedList : List<T>
{
    virtual void add(T item) = 0;
    virtual T least() = 0;
    virtual T greatest() = 0;
    virtual T get(int i) = 0;
    virtual int indexOf(T item) = 0;
    virtual void remove(int i) = 0;
    virtual List<T> searchRange(T from, T to) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

template <typename T>
class LinkedSortedList : SortedList<T>
{
public:

    // default constructor for LinkedSortedList
    LinkedSortedList()
    {
        // make a fictitious first node
        // we assume that value of this node is always less then the value of the first item
        auto emptyNode = new Node();
        first = emptyNode;
    }

    // add a new element to the List
    void add(T item)
    {
        listSize++; // increase the size of the list

        // if the list is empty we simply insert the item
        if (listSize == 0)
        {
            auto newNode = new Node();
            last = newNode; // automatically, it is the last one
            newNode->data = item;
            newNode->next = nullptr;
            return;
        }

        // go through each node until we find the one that is greater than the item
        auto *currentNode = first;
        while (currentNode->next != nullptr && item > currentNode->next->data)
        {
            currentNode = currentNode->next;
        }

        // insert the item right before the found node
        auto newNode = new Node();
        *newNode = { item, currentNode->next };
        currentNode->next = newNode;

        // if the item was inserted at the end, update the last-pointer
        if (newNode->next == nullptr)
        {
            last = newNode;
        }
    }

    T least()
    {
        return first->next->data;
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
        // raise an exception if i is invalid
        if (i < 0 || i >= listSize) throw exceptions::IndexOutOfBoundsException();

        // go to i'th element
        auto *currentNode = first;

        for (int j = 0; j < i; ++j) {
            currentNode = currentNode->next;
        }

        // delete it
        delete &currentNode->next->data;
        currentNode->next = currentNode->next->next;

        // decrease the size of the array
        listSize--;
    }

    List<T> searchRange(T from, T to)
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
public:
    void printAll()
    {
        auto *currentNode = first->next;

        while (currentNode != nullptr)
        {
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }

        cout << endl;
    }
private:
    struct Node
    {
        T data;
        struct Node *next;
    };

    Node* first;
    Node* last;
    unsigned int listSize = 0;
};

int main() {
    LinkedSortedList<string> list;

    list.add("baby");
    list.add("monkey");
    list.add("abs");
    list.add("zorro");
    list.add("kilo");
    list.add("nigga");

    list.printAll();
    try {
        list.remove(6);
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    list.printAll();

    return 0;
}
