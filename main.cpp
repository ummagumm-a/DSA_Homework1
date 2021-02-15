/**
 * This is the first homework for DSA course in Innopolis University.
 *
 * Author - Sinii Viacheslav
 */

#include <iostream>
#include <exception>
#include <memory>

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

    class NoElementsInTheRange : public exception
    {
        virtual const char* what() const throw()
        {
            return "There are no elements in this range!";
        }
    };
}

template <typename T>
class List
{
public:
    virtual void add(T item) = 0;
    virtual T get(int i) = 0;
    virtual int indexOf(T item) = 0;
    virtual void remove(int i) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

template <typename T>
class SortedList : public List<T>
{
public:
    virtual void add(T item) = 0;
    virtual T least() = 0;
    virtual T greatest() = 0;
    virtual T get(int i) = 0;
    virtual int indexOf(T item) = 0;
    virtual void remove(int i) = 0;
    virtual List<T>* searchRange(T from, T to) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

template <typename T>
class LinkedSortedList : public SortedList<T>
{
private:
    struct Node
    {
        T data;
        struct Node *next;
    };

    Node* first = nullptr;
    Node* last = nullptr;
    unsigned int listSize = 0;
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
        // if the list is empty we simply insert the item
        if (listSize++ == 0) // increase the size of the list
        {
            auto newNode = new Node();
            newNode->data = item;
            newNode->next = nullptr;
            first->next = newNode;
            last = newNode;
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

    void addLast(T item)
    {
        auto node = new Node();
        if (this->size() != 0)
            last->next = node;
        else
            first->next = node;
        node->data = item;
        last = node;
        listSize++;
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
        return getNode(i)->data;
    }

    int indexOf(T item)
    {
        auto currentNode = first->next;

        for (int i = 0; i < listSize; ++i) {
            if (currentNode->data == item) return i;

            currentNode = currentNode->next;
        }

        return -1;
    }

    void remove(int i)
    {
        auto node = getNode(i);
        // delete it
        delete &node->data;
        node->next = node->next;

        // decrease the size of the array
        listSize--;
    }

    List<T>* searchRange(T from, T to)
    {
        if (greatest() < from || least() > to) throw exceptions::NoElementsInTheRange();

        auto list = new LinkedSortedList<T>;
        auto currentNode = first->next;

        for (int i = 0; i < listSize; ++i) {
            if (currentNode->data >= from && currentNode->data <= to)
            {
                list->addLast(currentNode->data);
            }

            currentNode = currentNode->next;
        }

        return list;
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
    struct Node* getNode(int i)
    {
        // raise an exception if i is invalid
        if (i < 0 || i >= listSize) throw exceptions::IndexOutOfBoundsException();

        // go to i'th element
        auto *currentNode = first;

        for (int j = 0; j < i; ++j) {
            currentNode = currentNode->next;
        }

        return currentNode->next;
    }
};

int main() {
    LinkedSortedList<string> list;

    list.add("baby");
    list.add("monkey");
    list.add("abs");
    list.add("zorro");
    list.add("kilo");
    list.add("nigga");

/*    LinkedSortedList<int> list;

    list.add(5);
    list.add(3);
    list.add(9);
    list.add(0);
    list.add(-1);
    list.add(7);*/

    list.printAll();

    auto rangeList = list.searchRange("b" , "n");
    for (int i = 0; i < rangeList->size(); ++i) {
        cout << rangeList->get(i) << endl;
    }

    return 0;
}
