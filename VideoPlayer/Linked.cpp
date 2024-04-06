#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "Linked.h"


int Linked::getCurrentNode() const
{
    return playingNode;
}

void Linked::setCurrentNode(int newCurrentNode)
{
    playingNode = newCurrentNode;
}

int Linked::getMySize() const
{
    return mySize;
}

Linked::Linked()
    : first(0), last(0), mySize(0)
{}

//

Linked::~Linked() {
    NodePointer ptr = first, newptr;
    while (ptr != NULL) {
        newptr = ptr->next;
        delete ptr;
        ptr = newptr;
        if (ptr == first) {
            break;
        }
    }
    mySize = 0;
    first = nullptr;
    last = nullptr;
}

//

bool Linked::empty() {
    if (mySize == 0)
        return true;
    else
        return false;
}
//

void Linked::deletion(int index) {
    if (empty()) {
        return;
    }
    // index = (index % mySize + mySize) % mySize;

    NodePointer ptr = first;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    if (mySize == 1) {
        first = nullptr;
    }
    else {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        if (ptr == first) {
            first = ptr->next;
        }
    }

    delete ptr;
    mySize--;
}


//

void Linked::insert(ElementType value, int index) {
    NodePointer newPointer = new Node(value);

    if (index < 0 || index > mySize) {
        delete newPointer;
        cerr << "Error! Index out of range" << endl;
        return;
    }

    if (mySize == 0) {
        first = newPointer;
        last = newPointer;
    }
    else if (index == 0) {
        newPointer->next = first;
        newPointer->prev = last;
        first->prev = newPointer;
        last->next = newPointer;
        first = newPointer;
    }
    else if (index == mySize) {
        newPointer->prev = last;
        newPointer->next = first;
        last->next = newPointer;
        first->prev = newPointer;
        last = newPointer;
    }
    else {
        NodePointer current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        newPointer->prev = current->prev;
        newPointer->next = current;
        current->prev->next = newPointer;
        current->prev = newPointer;
    }
    mySize++;
}

//

void Linked::display(ostream& out) const {
    NodePointer pointer = first;
    if (mySize == 0) {
        return;
    }
    else {
        for (int i = 0; i < mySize; i++) {
            out << pointer->data;
            pointer = pointer->next;
        }
    }
}
//

Linked::Linked(const Linked& orig)
    : first(nullptr), last(nullptr), mySize(orig.mySize) {
    if (mySize == 0) return;

    NodePointer origptr = orig.first;
    NodePointer newNext = nullptr;

    first = new Node(origptr->data);
    newNext = first;
    origptr = origptr->next;

    while (origptr != orig.first) {
        NodePointer newNode = new Node(origptr->data);
        newNode->prev = newNext;
        newNext->next = newNode;

        newNext = newNode;
        origptr = origptr->next;
    }
    last = newNext;
    last->next = first;
    first->prev = last;

}

//

const Linked& Linked::operator=(const Linked& rhs) {
    mySize = rhs.mySize;
    if (mySize == 0) {
        this->~Linked();
        first = 0;
        last = 0;
        return *this;
    }
    if (this != &rhs) {
        this->~Linked();
        mySize = rhs.mySize;
        NodePointer origptr = rhs.first;
        NodePointer newNext = nullptr;

        first = new Node(origptr->data);
        newNext = first;
        origptr = origptr->next;

        while (origptr != rhs.first) {
            NodePointer newNode = new Node(origptr->data);
            newNode->prev = newNext;
            newNext->next = newNode;

            newNext = newNode;
            origptr = origptr->next;
        }

        last = newNext;
        last->next = first;
        first->prev = last;
    }
    return *this;
}

//

void Linked::shuffle() {
    NodePointer current = first;
    int size = mySize;

    srand(static_cast<unsigned>(time(0))); //time(0) to generate diffrent nums everytime, static cast bychange gtype to unsigned(non negative nums)
    for (int i = size - 1; i > 0; i--) { // fisher yates shufle method
        int j = rand() % (i + 1);

        NodePointer nodeI = current;
        for (int k = 0; k < i; k++) { //b loop lhad ma amsk el i zat nafsaha el bnb2ha mn ela kher
            nodeI = nodeI->next;
        }

        NodePointer nodeJ = current;
        for (int k = 0; k < j; k++) { // bloop lhad ma amsl el rand index el tl3ly
            nodeJ = nodeJ->next;
        }

        ElementType temp = nodeI->data;
        nodeI->data = nodeJ->data;
        nodeJ->data = temp;

        current = current->next; // 3shan fl next itteration yb2a 3arf eh hanbda2 mn fen
    }
}

//

bool Linked::search(ElementType value) {
    if (empty()) {
        return false;
    }
    NodePointer current = first;
    while (current != first) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
   // cout << "o";
    return false;
}

//
ElementType Linked::gbi(int currentNode) {
    if (empty() || currentNode < 0 || currentNode >= mySize) {
        return "error";

    }
    NodePointer current = first;
    for (int i = 0; i < currentNode; i++) {
        current = current->next;
    }
    return current->data;
}

//
ElementType Linked::nextNode(int currentNode) {
    if (empty() || currentNode < 0 || currentNode > mySize) {
        return "error";

    }
    if(currentNode == mySize)
        return first->data;
    NodePointer current = first;
    for (int i = 0; i < currentNode +1; i++) {
        i=i%mySize;
        current = current->next;
    }
    return current->data; //% 3shan ma yetla3sh bara el index bta3to
}

//

ElementType Linked::previous(int currentNode) {
    if (empty() || currentNode < 0 || currentNode >= mySize) {
        //cerr << "Error";
        return "Error";
    }
    NodePointer current = first;
    for (int i = 0; i < currentNode -1; i++) {
        i=i%mySize;
        current = current->prev;
    }
    return current->data; // %3shan ma yetla3sh bara el index bta3to
    // w +mysize 3shan ma ytl3sh ay rakam negative
}

//

ostream& operator<<(ostream& out, const Linked& aList) {
    aList.display(out);
    return out;

}

void Linked::edit(int index, ElementType value) {

    NodePointer ptr = first;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    ptr->data = value;
}

