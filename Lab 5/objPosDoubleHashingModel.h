#ifndef OBJPOS_DOUBLE_HASHING_MODEL_H
#define OBJPOS_DOUBLE_HASHING_MODEL_H

#include "objPosHash.h"
#include "objPos.h"

class objPos;

class objPosDoubleHashingModel : public objPosHashTable
{
    private:
        int calculateHashing(int prefix, int number) const;  // hashing function
        int calculateSecondaryHashing(int input) const;     // secondary hashing function
                                                      // signature subject to change

    public:
        objPosDoubleHashingModel();
        objPosDoubleHashingModel(int);
        virtual ~objPosDoubleHashingModel();

        bool insert(const objPos &thisPos);
        bool remove(const objPos &thisPos);  // lazy delete 
        bool isInTable(const objPos &thisPos) const;
        double getLambda() const;
        void printMe() const;
};

#endif