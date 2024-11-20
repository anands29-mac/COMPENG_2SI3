#ifndef OBJPOSSTACKMODEL_H
#define OBJPOSSTACKMODEL_H

#include "objPos.h"
#include "objPosList.h"

class objPos;

class objPosStackModel  // use Composition
{
    private:
        objPosList* myList;  // objPosDLinkedList

        void generateObjects(int count);
        int sortByTenScoreBS();  

    public:
        objPosStackModel();
        ~objPosStackModel();

        void populateRandomElements(int size);

        void push(const objPos &thisPos) const;
        objPos pop();
        objPos top();
        int size();        

        void printMe();
};

#endif