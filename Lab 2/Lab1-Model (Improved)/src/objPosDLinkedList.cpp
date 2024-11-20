#include "objPosDLinkedList.h"
#include <iostream>
using namespace std;

// Develop the objPos Doubly Linked List here.  
// Use the Test cases Test.cpp to complete the Test-Driven Development

objPosDLinkedList::objPosDLinkedList()
{
    
    listHead = new DNode();
    listTail = new DNode();

    listHead->next = listTail;
    listTail->prev = listHead;

    persistHead = listHead->next;

    listSize = 0;
}

objPosDLinkedList::~objPosDLinkedList()
{
    DNode* curr = listHead;

    while(curr->next != nullptr)
    {
        curr = curr->next;
        delete curr->prev;
    }

    delete listHead;
    delete listTail;

    persistHead = nullptr;
}

int objPosDLinkedList::getSize()
{
    return listSize;
}

bool objPosDLinkedList::isEmpty()
{
    return listSize == 0;
}

void objPosDLinkedList::insertHead(const objPos &thisPos)
{
    DNode* newHead = new DNode();
    newHead->data = thisPos;

    newHead->next = listHead->next;
    newHead->prev = listHead;

    if(listHead->next != nullptr){
        listHead->next->prev = newHead;
    } else{
        listTail = newHead;
    }

    listHead->next = newHead;
    
    listSize++; 
}



void objPosDLinkedList::insertTail(const objPos &thisPos)
{
  DNode* newTail = new DNode();
    newTail->data = thisPos;

    newTail->next = listTail;
    newTail->prev = listTail->prev;

    if(listTail->prev != nullptr){
        listTail->prev->next = newTail;
     } else{
        listHead->next = newTail;
     }
     listTail->prev = newTail;
    
    listSize++;
}

void objPosDLinkedList::insert(const objPos &thisPos, int index)
{
   if(index <= 0)
    {
        insertHead(thisPos);
        return;
    }

    else if (index >= listSize)
    {
        insertTail(thisPos);
        return;
    }

    DNode* new_node = new DNode();
    new_node->data = thisPos;        // Creates a new node for the inputted objPos

    DNode* prev;
    DNode* next;
    prev = listHead;

    int i = 0;

    while(prev->next != nullptr && i != index-1)
    {
        prev = prev->next;
        i++;
    }

    next = prev->next;

    prev->next = new_node;
    new_node->prev = prev;

    next->prev = new_node;
    new_node->next = next;

    listSize++;

}

objPos objPosDLinkedList::getHead() const
{
    if (listHead == nullptr) {
        return objPos();
    }
    return (listHead->next)->data;
  
}

objPos objPosDLinkedList::getTail() const
{
    if (listTail == nullptr) {
        return objPos();
    }
    return (listTail->prev)->data;
}

objPos objPosDLinkedList::get(int index) const
{
    if(index <= 0)
    {
        return getHead();
    }

    else if(index >= listSize-1)
    {
        return getTail();
    }

    DNode* curr;
    curr = listHead->next;

    int i = 0;

    while(curr->next != listTail && i != index)
    {
        curr = curr->next;
        i++;
    }

    return curr->data;

}

objPos objPosDLinkedList::getNext()
{
    if(persistHead->next != nullptr)
    {
        persistHead = persistHead->next;

        return (persistHead->prev)->data;
    }

    else
    {
        resetReadPos();

        objPos invalid(-99, 0, 0, 0, 0);

        return invalid;
    }

}

void objPosDLinkedList::resetReadPos()
{
    persistHead = listHead->next;
}

void objPosDLinkedList::set(const objPos &thisPos, int index)
{
     if(index < 0)
    {
        index = 0;
    }

    else if (index > listSize - 1)
    {
        index = listSize - 1;
    }
    
    DNode* curr;
    curr = listHead->next;

    int i = 0;

    while(curr->next != nullptr && i != index)
    {
        curr = curr->next;
        i++;
    }

    curr->data = thisPos;

}


objPos objPosDLinkedList::removeHead()
{
    if(listSize == 0)
    {
        objPos invalid(-99, 0, 0, 0, 0);

        return invalid;
    }

    DNode* temp = listHead->next;
    objPos deletedData = temp->data;

    listHead->next = temp->next;
    (temp->next)->prev = listHead;

    delete temp;
    listSize= listSize-1;

    return deletedData;
}

objPos objPosDLinkedList::removeTail()
{
    if(listTail == 0)
    {
        objPos invalid(-99, 0, 0, 0, 0);

        return invalid;
    }

    DNode* temp = listTail->prev;
    objPos deletedData = temp->data;
    
    (temp->prev)->next = listTail;
    listTail->prev = temp->prev;

    delete temp;
    listSize--;

    return deletedData;

}

objPos objPosDLinkedList::remove(int index)
{
   if(index <= 0)
    {
        return removeHead();
    }

    if(index >= listSize-1)
    {
        return removeTail();
    }

    if(listSize == 0)
    {
        objPos invalid(-99, 0, 0, 0, 0);  //shows an invalid element

        return invalid;
    }

    DNode* current;
    current = listHead->next;

    int i = 0;

    while(i != index)
    {
        current = current->next;
        i++;
    }

    DNode* prev = current->prev;
    DNode* next = current->next;

    prev->next = next;
    next->prev = prev;

    current->next = nullptr;
    current->prev = nullptr;

    listSize--;

    return current->data;

}


void objPosDLinkedList::printList() const
{
    cout << "[Head] <- ";

    DNode* curr;
    curr = listHead->next;

    while(curr != listTail)
    {
        cout << "(" << curr->data.getSym() << ", X = " << curr->data.getX() << ", Y = " << curr->data.getY() << ") <-- ";

        curr = curr->next;
    }


}


