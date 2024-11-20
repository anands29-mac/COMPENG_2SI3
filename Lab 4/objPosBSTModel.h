#ifndef OBJPOSTREEMODEL_H
#define OBJPOSTREEMODEL_H

#include "objPos.h"

class objPos;

class TNodeModel
{
    public:
        objPos data;
        TNodeModel *left;
        TNodeModel *right;

        TNodeModel(const objPos &thisPos)
        {
            data = thisPos;
            left = nullptr;
            right = nullptr;
        }
};

// This tree is sorted using Prefix
class objPosBSTModel
{
    private:
        TNodeModel *root;

        // Private Recursive Functions
        void deleteTree(const TNodeModel* thisNode);                
        void printTree(const TNodeModel* thisNode) const;        
        bool isInTree(const objPos& thisPos, const TNodeModel* thisNode) const;
        void insert(const objPos &thisPos, TNodeModel* &thisNode);
        void remove(const objPos &thisPos, TNodeModel* &thisNode);
        bool isLeaf(const objPos &thisPos, const TNodeModel* thisNode) const;
        const TNodeModel* findMin(const TNodeModel* thisNode) const;
        bool findGreater(const int numThreshold, const TNodeModel* thisNode) const;

    public:
        objPosBSTModel();
        ~objPosBSTModel();

        void deleteTree();
        bool isEmptyTree() const;
        void printTree() const;
        bool isInTree(const objPos &thisPos) const;
        void insert(const objPos &thisPos);
        void remove(const objPos &thisPos);
        bool isLeaf(const objPos &thisPos) const;        
        bool findGreater(const int numThreshold) const;
};

#endif