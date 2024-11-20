#include "objPosArrayList.h"
#include <iostream>
using namespace std;

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    currentPos = 0;
    arrayCapacity = DEFAULT_ARRAY_LIST_SIZE;

    list = new objPos[DEFAULT_ARRAY_LIST_SIZE]; 
}

objPosArrayList::~objPosArrayList()
{
    delete[] list;
}


int objPosArrayList::getSize()
{
    return listSize;  // Theta(1)
} // Theta(1)

bool objPosArrayList::isEmpty()
{
    return (listSize == 0);
}


void objPosArrayList::insertHead(const objPos &thisPos)
{

    if(listSize == arrayCapacity) return;  // T1 = Theta(1) = Theta best case

    // The rest will be our estimation of Theta worst case
    
    for(int i = listSize; i > 0; i--)  // T2 = Theta(n)
    {
        list[i] = list[i-1];  // can do this because of copy constructor
        // T3 = Theta(1)
    }
    
    list[0].setX(thisPos.getX());   // T4 = Theta(1)
    list[0].setY(thisPos.getY());   // T5 = Theta(1)
    list[0].setNum(thisPos.getNum());  // T6 = Theta(1)
    list[0].setPF(thisPos.getPF()); // T7 = Theta(1)
    list[0].setSym(thisPos.getSym());  // T8 = Theta(1) 

    //list[0].printObjPos();

    listSize++;   // T9 = Theta(1)
}
// T = bestcase{T1}, worstcase{T2*T3+sum(T4:T9)}
// T = Theta, bestcase(1)
// T = Theta, worstcase(n*1+6) = Theta, worstcase(n)
// T = O(n) = {Theta(n), Theta(1), Theta(n^0.5)....}  (anything growing slower or equal to n)
//   = o(n^2) = {Theta(n), Theta(1), Theta(n^0.5)....}  (anything growing slower to n^2)

void objPosArrayList::insertTail(const objPos &thisPos)
{
    if(listSize == arrayCapacity) return;

    list[listSize].setX(thisPos.getX());
    list[listSize].setY(thisPos.getY());
    list[listSize].setNum(thisPos.getNum());
    list[listSize].setPF(thisPos.getPF());
    list[listSize].setSym(thisPos.getSym());

    //list[listSize].printObjPos();

    listSize++;
}

void objPosArrayList::insert(const objPos &thisPos, int index)
{
    if(listSize == arrayCapacity) return;          // Tbestcase = Theta, bestcase(1)

    if(index > listSize) index = listSize;        // Theta(1)
    if(index < 0) index = 0;                      // Theta(1)

    for(int i = listSize; i > index; i--)         // Theta, bestcase(1)  when index is at or beyond the last element
                                                  // Theta, worstcase(n)  when index is at the head of the list
    {
        list[i] = list[i-1];     // Theta(1)
    }

    list[index].setX(thisPos.getX());        // Theta(1)
    list[index].setY(thisPos.getY());     // Theta(1)
    list[index].setNum(thisPos.getNum());     // Theta(1)
    list[index].setPF(thisPos.getPF());     // Theta(1)
    list[index].setSym(thisPos.getSym());     // Theta(1)

    //list[index].printObjPos();

    listSize++;     // Theta(1)
}   // if line 77 is triggered, T = Theta(1)  - best case 1
    // if index is at the last element of the list or beyond...
    //      T = Theta(1 + 1 + 1*1 + 6) = Theta(9) = Theta(1)   - best case 2 (larger leading constant than best case 1)
    // if index is at the head of the list...Worst Case
    //      T = Theta(1 + 1 + n*1 + 6) = Theta(n + 8) = Theta(n)  - worst case

    // T = Theta, bestcase(1), Theta, worstcase(n)
    //   = O(n) = {Theta(n), Theta(1), Theta(n^0.5), ...}
    //   = o(n^2) = {Theta(n), Theta(1), Theta(n^0.5), ...}


objPos objPosArrayList::getHead() const
{
    return list[0];  // thanks to copy constructor
}

objPos objPosArrayList::getTail() const
{
    return list[listSize-1];
}

objPos objPosArrayList::get(int index) const
{
    if(index < 0) index = 0;
    if(index > listSize - 1) index = listSize - 1;

    return list[index];
}

objPos objPosArrayList::getNext()
{
    //cout << "current head position: " << currentPos << endl;
    
    if(currentPos == listSize) // Theta(1)
    {
        cerr << "reader head reaching the END!" << endl; // Theta(1)
        currentPos = 0; // Theta(1)
        return objPos(-99,0,0,0,0); // indicating end of list // copy constructor  // Theta(1)
    }
 
    return list[currentPos++]; // copy constructor // Theta(1)
}  // Theta(1)

void objPosArrayList::resetReadPos()
{
    currentPos = 0;  // Theta(1)
} // Theta(1)

void objPosArrayList::set(const objPos &thisPos, int index)
{
    if(index < 0) index = 0;
    if(index > listSize - 1) index = listSize - 1;

    list[index].setX(thisPos.getX());
    list[index].setY(thisPos.getY());
    list[index].setNum(thisPos.getNum());
    list[index].setPF(thisPos.getPF());
    list[index].setSym(thisPos.getSym());
}


objPos objPosArrayList::removeHead()
{
    if(listSize <= 0) 
        return objPos(-99,0,0,0,0); // indicating invalid element
    
    objPos temp = list[0];

    for(int i = 0; i < listSize - 1; i++)
    {
        list[i] = list[i+1];
    }

    listSize--;

    return temp;
}

objPos objPosArrayList::removeTail()
{
    if(listSize <= 0)   // Theta(1)
        return objPos(-99,0,0,0,0); // objPos constructor is called  // Theta(1)

    listSize--;  // lazy delete // Theta(1)

    return list[listSize];  // return the lazy-deleted element   
    // returning objPos instance through the stack will invoke copy constructor of objPos
     // Theta(1)
 } // T = Theta(1)

objPos objPosArrayList::remove(int index)
{
    objPos temp;  // call default constructor
    if(listSize <= 0) 
        return objPos(-99,0,0,0,0); // indicating invalid element
    
    if(index > listSize) index = listSize - 1;
    if(index < 0) index = 0;

    temp = list[index];

    for(int i = index; i < listSize - 1; i++)
    {
        list[i] = list[i+1];
    }

    listSize--;

    return temp;
}


void objPosArrayList::printList() const
{
    cout << "List Contains:" << endl;
    
    for(int i = 0; i < listSize; i++)
    {
        cout << "[" << i << "] ";
        list[i].printObjPos();
    }

    cout << "END OF LIST" << endl;
}

