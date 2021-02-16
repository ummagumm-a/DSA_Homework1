/**
 * This is the first homework for DSA course in Innopolis University.
 *
 * Author - Sinii Viacheslav
 */

/*
 * When testing the code, I searched an empty list,
 * deleted first, last, and middle elements,
 * inserted least, greatest and mid elements,
 * tried to search elements in unsuitable range,
 * tried to access elements with wrong index,
 * checked on the size of the list after deletions.
 */

#include <iostream>
#include <exception>
#include <iomanip>

using namespace std;

// a bunch of exceptions
namespace exceptions
{
    // this exception is thrown in case if user tries to reach element by an invalid index
    class IndexOutOfBoundsException : public exception
    {
        virtual const char* what() const throw()
        {
            return "Index out of bounds!";
        }
    };

    // this exception is thrown in case if there are no elements in a requested range
    class NoElementsInTheRange : public exception
    {
        virtual const char* what() const throw()
        {
            return "There are no elements in this range!";
        }
    };

    // this exception is thrown in case if a user tries to access elements in an empty list
    class NoElementsInTheListException : public exception
    {
        virtual const char* what() const throw()
        {
            return "The list is empty, dummy!";
        }
    };

    // this exception is thrown in case if a user tries to insert not the greatest element using addLast() method
    class InvalidUseOfAddLastException : public exception
    {
        virtual const char* what() const throw()
        {
            return "Don't use addLast() with this element!";
        }
    };
}

// base class for all lists
template <typename T>
class List {
    virtual void add(T item) = 0;
    virtual T get(int i) = 0;
    virtual int indexOf(T item) = 0;
    virtual void remove(int i) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

// base class for all sorted lists (obviously, is a list itself)
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

// my implementation of a sorted list with use of singly linked list
template <typename T>
class LinkedSortedList : public SortedList<T>
{
private:
    // a struct which describes one single node which contains some data and a pointer to the next element
    struct Node
    {
        T data;
        struct Node *next{};
    };

    // pointers on the first(dummy) and the last (for faster access to the greatest element) elements
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
    // O(n) - worst case
    void add(T item)
    {
        // if the list is empty we simply insert the item
        if (listSize++ == 0) // increase the size of the list
        {
            // create new node
            auto newNode = new Node();
            newNode->data = item;
            newNode->next = nullptr;
            // update pointers
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

    // use only if you are sure that the added item is the new greatest
    // O(1) - worst case
    void addLast(T item)
    {
        // if the item is not the new greatest - throw an exception
        try {
            if (item < greatest()) throw exceptions::InvalidUseOfAddLastException();
        } catch (exception& e) {

        }

        // insert the item
        auto node = new Node();
        if (this->size() != 0)
            last->next = node;
        else
            first->next = node;

        node->data = item;
        last = node;

        // increase the size
        listSize++;
    }

    // return the least element in the list
    // O(1) - worst case
    T least()
    {
        // if the list is empty - there is no least element
        if (listSize == 0) throw exceptions::NoElementsInTheListException();

        return first->next->data;
    }

    // return the least element in the list
    // O(1) - worst case
    T greatest()
    {
        // if the list is empty - there is no greatest element
        if (listSize == 0) throw exceptions::NoElementsInTheListException();

        return last->data;
    }

    // return an element at index i
    // O(n) - worst case
    T get(int i)
    {
        // if the list is empty - there is nothing to return
        if (listSize == 0) throw exceptions::NoElementsInTheListException();

        return getNode(i)->data;
    }

    // find the index of some item
    // O(n) - worst case
    int indexOf(T item)
    {
        auto currentNode = first->next;

        // go through each element in the list until we find the right one
        for (int i = 0; i < listSize; ++i) {
            if (currentNode->data == item) return i;

            currentNode = currentNode->next;
        }

        // indicator that there is no such element in the list
        return -1;
    }

    // function for removing element in index i
    // O(n) - worst case
    void remove(int i)
    {
        auto node = getNode(i - 1);
        // free the memory from the data
        delete &node->next->data;
        // update the pointer of the previous element
        node->next = node->next->next;

        // if the last element was deleted - update the 'last' pointer
        if (node->next == nullptr)
        {
            last = node;
        }

        // decrease the size of the array
        listSize--;
    }

    // function that returns elements between 'from' and 'to'
    // O(n) - worst case
    // In the worst case, which is if the right bound is greater or equal to the last element,
    // we will go until the end of the list
    List<T>* searchRange(T from, T to)
    {
        // if all elements are obviously not in the range
        if (greatest() < from || least() > to)
        {
            throw exceptions::NoElementsInTheRange();
        }

        // you can't search in the empty list
        auto currentNode = first->next;
        if (currentNode == nullptr)
        {
            cout << "nullptr";
            throw exceptions::NoElementsInTheListException();
        }

        // go through each element in the list and add the ones from the range to the new list
        auto list = new LinkedSortedList<T>;
        for (int i = 0; i < listSize; ++i) {
            // if all succeeding elements are obviously not in the range
            if (currentNode->data > to) break;

            if (currentNode->data >= from && currentNode->data <= to)
            {
                list->addLast(currentNode->data);
            }

            currentNode = currentNode->next;
        }

        return list;
    }

    // this function returns the size of the list
    // O(1) - worst case
    int size()
    {
        return listSize;
    }

    // this function tells whether this list is empty
    // O(1) - worst case
    bool isEmpty()
    {
        return listSize == 0;
    }
public:
    // this function prints all elements in the list to the standard output
    // O(n) - worst case
    void printAll()
    {
        auto *currentNode = first->next;

        // go through each element and print it
        while (currentNode != nullptr)
        {
            ostringstream oss;
            oss << (string) currentNode->data;
            if (currentNode->next != nullptr) oss << ", ";

            cout << oss.str();

            currentNode = currentNode->next;
        }

        cout << endl;
    }
private:
    // get the node at index i
    // O(n) - worst case
    struct Node* getNode(int i)
    {
        i++;
        // raise an exception if i is invalid
        if (i < 0 || i >= listSize) throw exceptions::IndexOutOfBoundsException();

        // go to i'th element
        auto *currentNode = first;

        for (int j = 0; j < i; ++j) {
            currentNode = currentNode->next;
        }

        return currentNode;
    }
};

// this is a struct for a store item
struct Item
{
    double price;
    string name;

    // overloaded operators for comparison
    bool operator>(const Item& item)
    {
        return this->price > item.price;
    }

    bool operator==(const Item& item)
    {
        return this->price == item.price;
    }

    bool operator<(const Item& item)
    {
        return this->price < item.price;
    }

    bool operator>=(const Item& item)
    {
        return this->price >= item.price;
    }

    bool operator<=(const Item& item)
    {
        return this->price <= item.price;
    }

    // a string representation of the item
    operator string()
    {
        ostringstream os;
        os << fixed << setprecision(2);
        os << "$" << price << " " << name;
        return os.str();
    }
};

// a class describing a shop manager
class PawnShopManager
{
public:
    LinkedSortedList<Item> store;
public:
    // function to manage orders
    void takeOrder(const string& order)
    {
        // find indices of delimiters between entries of one order
        int indexOfDollarSign = order.find('$');
        int indexOfSecondSpace = order.find(' ', indexOfDollarSign);
        // extract those entries
        string firstEntry = order.substr(indexOfDollarSign + 1, indexOfSecondSpace - indexOfDollarSign - 1);
        string secondEntry = order.substr(indexOfSecondSpace + 1);

        if (order.rfind("ADD", 0) == 0) // if the order is to add new item
        {
            double price = stod(firstEntry);
            Item item = {price, secondEntry};

            store.add(item);
        }
        else if (order.rfind("REMOVE", 0) == 0) // if the order is to remove an element in the list
        {
            double price = stod(firstEntry);
            Item item = {price, secondEntry};

            try {
                store.remove(store.indexOf(item));
            } catch (exception& e) {

            }
        }
        else if (order.rfind("LIST", 0) == 0) // if the order is to return a list of elements in some range
        {
            double lowerPrice = stod(firstEntry);
            double upperPrice = stod(secondEntry.substr(1));

            // if there are no elements in this range - return an empty list
            LinkedSortedList<Item>* range;
            try {
                range = reinterpret_cast<LinkedSortedList<Item>*>(
                        store.searchRange({ lowerPrice, " " }, { upperPrice, " " })
                );
            } catch (exception& e) {
                range = new LinkedSortedList<Item>;
            }

            range->printAll();
        }
    }
};

int main() {
    PawnShopManager manager;

    string order;
    int n;
    cin >> n;
    getline(cin, order);
    for (int i = 0; i < n; ++i) {
        getline(cin, order);
        manager.takeOrder(order);
    }

    return 0;
}