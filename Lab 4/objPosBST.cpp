#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    // Constructor (Check Lecture Notes for Implementation, Simple)
    root=nullptr;
}

objPosBST::~objPosBST()
{
    // Destructor
    // Invoke delete tree, then set root to NULL

    deleteTree();
}




void objPosBST::deleteTree(const TNode* thisNode)
{
	// Delete all nodes in the tree

    // Question from Class - Which Traversal Order should you use for this method?
    //   WARNING - using the wrong one will result in potential heap error.
    if (thisNode==nullptr)
        return;

    deleteTree(thisNode->left);        //PostOrder TRaversal method is used to safely delete all the elements
    deleteTree(thisNode->right);
    delete thisNode;
}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
    root = nullptr;
}


bool objPosBST::isEmptyTree() const
{
    // Check if tree is empty
    //  Really simple, think about how.
    return root==nullptr;

}



// Public Interface, Implemented
void objPosBST::printTree() const
{    
    if(root == NULL)
    {
        cout << "[Empty]";
        return;
    }
    printTree(root);  // recursive call on the private helper function
}

void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    // Print the entire tree content using **In-Order Traversal**

    // use printObjPos() method in objPos class for formatted print
    if (thisNode==nullptr)
    { 
        return;
    }
    
    printTree(thisNode->left);
    thisNode->data.printObjPos();
    printTree(thisNode->right);
            
}




// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, return true

    if (thisNode==NULL)
        return false;
    else if (thisPos.getPF()< thisNode->data.getPF())
        return isInTree(thisPos, thisNode->left);
    else if (thisPos.getPF() > thisNode->data.getPF())
        return isInTree(thisPos, thisNode->right);
    else
        return true;
}


// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    // Insert objPos as a Node into the BST

    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.

    // Modification: 
    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)
    if (thisNode==NULL)
        thisNode=new TNode(thisPos);
    else if (thisPos.getPF()< thisNode->data.getPF())
        insert(thisPos, thisNode->left);
    else if (thisPos.getPF()> thisNode->data.getPF())
        insert(thisPos, thisNode->right);
    else if (thisPos.getPF()==thisNode->data.getPF())
        thisNode->data.setNum(thisNode->data.getNum()+thisPos.getNum());

}




const TNode* objPosBST::findMin(const TNode* thisNode) const
{
	// Find the node with the smallest prefix in the subtree from thisNode

    // Used as part of remove() algorithm

    // Check Lecture Notes for implementation

    if (thisNode==NULL)
        return NULL;
    while (thisNode->left!=NULL)
        thisNode=thisNode->left;
    return thisNode;

    
}

void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
	// Remove the node with matching prefix of thisPos from the subtree thisNode

    // *IMPORTANT* Check Lecture Notes for general implementation
    //  Remember the three removal case scenarios

    // Case 1 and 2 both can be handled with one algorithm (Lecture Notes)

    // Case 3 - Delete the node with 2 children
    //   You can use either methods (check lecture notes)

    if (thisNode==NULL)
        return;
    if (thisPos.getPF()< thisNode->data.getPF())
        remove (thisPos, thisNode->left);
    else if (thisPos.getPF()> thisNode->data.getPF())
        remove (thisPos, thisNode->right);
    else if (thisNode->left !=NULL && thisNode->right !=NULL){
        //Case 3 (delete node with 2 childeren)

        thisNode->data=findMin(thisNode->right)->data;
        remove(thisNode->data, thisNode->right);
    }

    else {
            //Takes care of Case 1 & 2
            TNode* temp= thisNode;
            thisNode=(thisNode->left !=NULL) ? thisNode->left : thisNode->right;
            delete temp;
    }
    
}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}




bool objPosBST::isLeaf(const objPos &thisPos, const TNode* thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, check if the node is a leaf node

    // Remember, leaf nodes do not have children nodes

    if (thisNode==NULL)
        return false;
    else if (thisPos.getPF()<thisNode->data.getPF())
        return isLeaf(thisPos, thisNode->left);
    else if (thisNode->data.getPF()==thisPos.getPF())
        return (thisNode->left == nullptr && thisNode->right==nullptr);
    else
        return isLeaf(thisPos, thisNode->right);

}

// Public Interface, Implemented
bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root); // recursive call on the private helper function
}


bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold

    // WARNING - this one is not as straightforward.

    // Algorithm Suggestion
    //  1. If tree empty, just return false
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.

    // HINT:  If you do this right, the algorithm is less than 10 lines.

    if (thisNode==nullptr)
        return false;

    if(findGreater(numThreshold, thisNode->left))
            return true;
    if (findGreater(numThreshold, thisNode->right))
            return true;
    if (thisNode->data.getNum() > numThreshold)
            return true;
    return false;


    /*if (thisNode -> data.getNum()> numThreshold)
        return true;
    return findGreater(numThreshold, thisNode->left) || findGreater(numThreshold, thisNode->right);  */
}

// Public Interface, Implemented
bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root); // recursive call on the private helper function
}
