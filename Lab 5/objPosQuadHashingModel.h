#ifndef OBJPOS_QUADRATIC_HASHING_MODEL_H
#define OBJPOS_QUADRATIC_HASHING_MODEL_H

#include "objPosHash.h"
#include "objPos.h"

class objPos;

class objPosQuadHashingModel : public objPosHashTable
{
    private:        
        int calculateHashing(int prefix, int number) const;  // hashing function

    public:
        objPosQuadHashingModel();
        objPosQuadHashingModel(int);
        virtual ~objPosQuadHashingModel();

        bool insert(const objPos &thisPos);
        bool remove(const objPos &thisPos);  // lazy delete 
        bool isInTable(const objPos &thisPos) const;
        double getLambda() const;
        void printMe() const;
};

#endif