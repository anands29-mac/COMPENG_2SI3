#include "Player.h"
#include "objPosArrayList.h"
//#include "objPosDLinkedList.h"

#include <iostream>
using namespace std;

#define TEST_LENGTH 1000

Player::Player(int x, int y, char symbol, GameMechs* gm, ItemBin* bin)
{
   
    // Choose the list type for Lab 2
    myPos = new objPosArrayList();    
    //myPos = new objPosDLinkedList();

    // turn false for performance estimation in Lab 2
    killable = true;  
    
    // Configure TEST_LENGTH to validate your asymptotic analysis on movePlayer()
    // with killable turned off.
    // for(int i = 0; i < TEST_LENGTH; i++)
        myPos->insertHead(objPos(x, y, -1, 0, symbol));
       
    gmRef = gm;
    boardRef = gmRef->getBoardRef();
    binRef = bin;

    myDir = STOP;
    myScore = 0;

    gmRef->addPlayer(this);
}

Player::~Player()
{
    delete myPos;
}


void Player::updatePlayerFSM()  // private
{
    char cmd = gmRef->getCMD();   // Theta(1)
    switch(cmd)   // Theta(1)
    {
        case 'w':
        case 'W':
            if(myDir != DOWN) myDir = UP;   // Theta(1)
            break;

        case 's':
        case 'S':
            if(myDir != UP) myDir = DOWN;    // Theta(1)
            break;

        case 'a':
        case 'A':
            if(myDir != RIGHT) myDir = LEFT;    // Theta(1)
            break;

        case 'd':
        case 'D':
            if(myDir != LEFT) myDir = RIGHT;    // Theta(1)
            break;

        default:
            break;    // Theta(1)
    }
}   // Theta(1)

void Player::movePlayer()
{    
    updatePlayerFSM();   // Theta(1)
    if(myDir == STOP) return;    // Theta(1) - bestcase 1 (failed the sanity check)

    undrawPlayer(); // Theta(n)
    
    objPos currHeadPos = myPos->getHead();   // Theta(1)
    int inX = currHeadPos.getX();  // Theta(1)
    int inY = currHeadPos.getY();   // Theta(1)  
        
    switch(myDir) // Theta(1)
    {
        case UP:            
            if(--inY < 1)  // Theta(1)
                inY = gmRef->getBoardSizeY() - 2; // Theta(1)
            break;

        case DOWN:
            if(++inY > (gmRef->getBoardSizeY() - 2)) // Theta(1)
                inY = 1; // Theta(1)
            break;

        case LEFT:
            if(--inX < 1)  // Theta(1)
                inX = gmRef->getBoardSizeX() - 2; // Theta(1)
            break;

        case RIGHT:
            if(++inX > (gmRef->getBoardSizeX() - 2)) // Theta(1)
                inX = 1; // Theta(1)
            break;

        default:
            break; // Theta(1)
    } 

    currHeadPos.setX(inX);               // Theta(1)
    currHeadPos.setY(inY);// TARGET      // Theta(1)
    
    myPos->insertHead(currHeadPos);  // insert new head      // O(n)

    if(!checkCollision())            // check collision.  If collision never happened,  // Omega(1)
        myPos->removeTail();         // removeTail.  Otherwise, generate new item.    // Theta(1)
    
    if(killable)                          // Theta(1)
        if(checkSelfCollision())
            gmRef->setGameLost();       // If colliding with itself, end game.
     
}    // T, bestcase = Theta, bestcase(1)
     // due to O(n) on line 111
     //  T, bestcase = Theta(1)
     //  T, worstcase = Theta(n)
     // T = Theta(n+11) + O(n) = Theta(n) + O(n) = O(n) ##
     //                                          = o(n^2)  also OK

     // If checkCollision is not always false, then T = Omega(1) ##

    
bool Player::checkCollision()  // private
{    
    // 1. Check Item Bin for Item ObjPos
    objPos target = binRef->getItem();  // Theta(1)
    bool collided = myPos->getHead().isOverlap(&target); // Theta(1)

    // 2. check whether objPos are equal
    if(collided)// Theta(1)
    {
        // 3. If yes, collision takes place
        // Generate New Item(s)
        binRef->generateItem();// Omega(1)

        // Increase Score by Number
        myScore += target.getNum();// Theta(1)
    }

    return collided;// Theta(1)
}// Omega(1)

bool Player::checkSelfCollision()  // private
{    
    // Make sure snake is long enough to kill itself
    int length = myPos->getSize(); // Theta(1)
    if(length < 4) return false; // T, bestcase = Theta(1)

    // Then check for self collision
    myPos->resetReadPos(); // Theta(1)
    objPos tempPos; // Theta(1)
    objPos headPos = myPos->getNext();// Theta(1)

    // Best case - tempPos overlaps with headPos at i = 3 (why not 0, 1, or 2?)
        // Theta(1)
    // WOrst case - tempPos overlaps with headPos at i = length - 1 OR no overlap
        // Theta(n)
    for(int i = 1; i < length; i++) 
    {
        tempPos = myPos->getNext();// Theta(1)
        if(headPos.isOverlap(&tempPos))// Theta(1)
        {
            // set game end.
            return true;// Theta(1)
        }
    }

    return false;// Theta(1)
}
// T bestcase1 = Theta(1 + 1) = Theta(1)
// T bestcase2 = Theta(6 + 1*3) = Theta(9) = Theta(1)
// T worstcase = Theta(6 + n*3) = Theta(3n+6) = Theta(n)
// T = Theta, bestcase(1), Theta, worstcase(n)
//   = O(n) = o(n^2)



void Player::drawPlayer()  
{
    objPos targetPos;  // Theta(1)
    int scanSize = myPos->getSize();  // get the list size  // Theta(1)

    myPos->resetReadPos();  // Theta(1)
    for(int i = 0; i < scanSize; i++)  // Theta(n)
    {
        targetPos = myPos->getNext();  // Theta(1)
        boardRef[targetPos.getY()][targetPos.getX()] = targetPos.getSym();   // Theta(1)
    }  
}  // T = Theta(3 + n*(1+1)) = Theta(3 + 2n) = Theta(n)  ##
    

void Player::undrawPlayer()  // private helper function
{
    objPos targetPos;  // Theta(1)
    int scanSize = myPos->getSize();  // get the list size  // Theta(1)
 
    myPos->resetReadPos();  // Theta(1)
    for(int i = 0; i < scanSize; i++)  // Theta(n)
    {
        targetPos = myPos->getNext();  // Theta(1)
        boardRef[targetPos.getY()][targetPos.getX()] = ' ';  // Theta(1)
    }
}  // T = Theta(3 + n*(1+1)) = Theta(3 + 2n) = Theta(n)  ##
    


void Player::increaseScore()
{
    myScore++;
}

int Player::getScore() const
{
    return myScore;    
}

objPosList* Player::getPlayerPos() const
{
    return myPos;   // Theta(1)
}  // Theta(1)
    
