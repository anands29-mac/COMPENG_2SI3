#include "objPosStack.h"
#include "objPosDLinkedList.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

// Available Data Members from objPosStack.h (Must Review)
//
//      objPosList* myList
//      
//  This is the polymorphic list pointer to the underlying List data structure to
//   support all Stack functionalities
//
//  You should use objPosDLinkedList as your main design param


objPosStack::objPosStack()
{
    // Constructor
    //   Instantiate myList as objPosDLinkedList.  You may use objPosArrayList for testing purpose only.

    myList = new objPosDLinkedList;

}


objPosStack::~objPosStack()
{
    // Destructor
    //  Just delete myList (and all otherheap members, if any)

    delete myList;
}


// private helper function
void objPosStack::generateObjects(int count)
{
    // Generate and pushes individual objPos isntances with randomly generated Prefix, Number, and Symbol.
    // The total number of generated instances is capped by input variable **count**.
    
    // 1. Generate Prefix A-Z and a-z.  Alphabetic characters only.
    // 2. Generate Number [0, 99]
    // 3. Leave Symbol as *
    // Push every randomly generately objPos into the Stack.
    for (int i =0; i<count; i++)
    {
        char prefix=(rand()%2==0)? ('A'+rand()%26): ('a' +rand()%26);
        int number=rand()%100;
        char symbol='*';

        objPos newPos(0,0,prefix, number, symbol);
        push(newPos);
    }


}


// private helper function
int objPosStack::sortByTenScoreBS()
{
    // Use BUBBLE SORT to sort all the objPos instances in the Stack in ascending order using teh doigit of 10
    //  of the **number** field of objPos.

    // You can use the relevant insertion and removal methods from the objPosDLinkedList interface
    //  to complete the sorting operations.

    // Recommendation - use set() and get() - Think about how

    int n = myList->getSize();
    for (int i=0; i<n-1;i++){
        for (int j=0; j<n-i-1;j++){
            objPos pos1=myList->get(j);
            objPos pos2=myList->get(j+1);

            if ((pos1.getNum()/10)%10 > (pos2.getNum()/10)%10){
                myList->set(pos2,j);
                myList->set(pos1,j+1);
            }
        }
    }
    
}


void objPosStack::populateRandomElements(int size)
{
    // This function generates the number of randomly generated objPos instances with uninitialized
    //  x-y coordinate on the Stack, then sort them in ascending order using the digit of 10
    //  of the **number** field in objPos instances.

    // Implementation done.  You'd have to implement the following two private helper functions above.
    srand(time(NULL));
    generateObjects(size);
    sortByTenScoreBS();
}



void objPosStack::push(const objPos &thisPos) const
{
    // Push thisPos on to the Stack.
    //  Think about which objPosDLinkedList method can realize this operation.

    myList->insertHead(thisPos);
}

objPos objPosStack::pop()
{
    // Pop the top element of the Stack.
    //  If the Stack is empty, return objPos(-99, 0, 0, 0, 0)
    //  Think about which objPosDLinkedList methods can realize this operation.

    if (myList->isEmpty()){
        return objPos(-99,0,0,0,0);
    }
    return myList->removeHead();   

}

objPos objPosStack::top()
{
    // Return the top element of the Stack without removing it
    //  If the Stack is empty, return objPos(-99, 0, 0, 0, 0)
    //  Think about which objPosDLinkedList methods can realize this operation.

    if (myList->isEmpty())
    {
        return objPos(-99,0,0,0,0);
    }
    return myList->getHead();
}

int objPosStack::size()
{
    // Return the size of the Stack 
    //  Think about which objPosDLinkedList method can realize this operation.

    return myList->getSize();
}

void objPosStack::printMe()
{
    // NOT GRADED
    //  Print the contents of the Stack
    //  Think about which objPosDLinkedList method can partially realize this operation.

    // IMPORTANT: USE THIS METHOD FOR DEBUGGING!!!

    myList->printList();
}