#pragma once
#include <iostream>
using namespace std;

typedef string ElementType;

class Linked
{
private:

    class Node {
    public:
        ElementType data;
        Node* next;
        Node* prev;
        Node()
            : next(nullptr), prev(nullptr)
        {}
        Node(ElementType dataValue)
            : data(dataValue), next(nullptr), prev(nullptr)
        {}
    };

    typedef Node* NodePointer;
    NodePointer first;
    NodePointer last;

    int playingNode = -1;
    int mySize;

public:
    Linked();// default constructor

    Linked(const Linked& orig); //copy constructor ~Linked () ;

    ~Linked();//destructor

    const Linked& operator=(const Linked& rhs);// assignment operator

    bool empty();

    void insert(ElementType value, int index);

    void deletion(int index); //erase function void display (ostream & out) const;
    bool search(ElementType value);

    ElementType gbi(int index);

    ElementType nextNode(int currentNode);

    ElementType previous(int currentNode);

    void display(ostream& out) const;

    void shuffle();

    void edit(int index, ElementType value);

    int getCurrentNode() const;
    void setCurrentNode(int newCurrentNode);
    int getMySize() const;
};
ostream& operator<<(ostream& out, const Linked& aList);
