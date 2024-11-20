#include "ItemBin.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

ItemBin::ItemBin(GameMechs* gm)
{
    gmRef = gm;
    boardRef = gmRef->getBoardRef();  
    myItem = new objPos(12, 12, 32, 'A', '*');  

    srand(time(NULL));    
}

ItemBin::~ItemBin()
{
    delete myItem;
}

void ItemBin::drawItem()
{
    int x = myItem->getX();    // Theta(1)
    int y = myItem->getY();     // Theta(1)   
    char num[2];  // convert number to displayable chars      // Theta(1)
    DigitToChar(num);     // Theta(1)

    boardRef[y][x] = myItem->getSym();    // Theta(1)
    boardRef[y-1][x-1] = myItem->getPF();    // Theta(1)
    boardRef[y-1][x] = num[0];    // Theta(1)
    boardRef[y-1][x+1] = num[1];    // Theta(1)
}      // Theta(1)

void ItemBin::undrawItem()
{
    int x = myItem->getX();   // Theta(1)
    int y = myItem->getY();// Theta(1)

    boardRef[y][x] = ' ';// Theta(1)
    boardRef[y-1][x-1] = ' ';// Theta(1)
    boardRef[y-1][x] = ' ';// Theta(1)
    boardRef[y-1][x+1] = ' ';// Theta(1)
}// Theta(1)

void ItemBin::DigitToChar(char result[])
{
    int number = myItem->getNum();     // Theta(1)
    result[0] = (number / 10) + '0';      // Theta(1)
    result[1] = (number % 10) + '0';    // Theta(1)
}    // Theta(1)


void ItemBin::generateItem()
{
    // Step 1: Get Player Ref from GameMech for Player pos
    Player** plList = gmRef->getPlayerListRef();          // Theta(1)
    objPosList *playerPos = plList[0]->getPlayerPos();    // Theta(1)

    //int bitVec[gmRef->getBoardSizeX()][gmRef->getBoardSizeY()]= {0};

    // to prevent stack overflow
    int xsize = gmRef->getBoardSizeX();
    int ysize = gmRef->getBoardSizeY();
    int** bitVec = new int*[xsize];
    for(int i = 0; i < xsize; i++)
    {
        bitVec[i] = new int[ysize];
        for(int j = 0; j < ysize; j++)
            bitVec[i][j] = 0;
    }
       


    int playerLength = playerPos->getSize();    // Theta(1)

    objPos target;  // Theta(1)
    playerPos->resetReadPos();  // Theta(1)

    for(int i = 0; i < playerLength; i++) // Theta(n)
    {
        target = playerPos->getNext();  // Theta(1)
        bitVec[target.getX()][target.getY()] = 1;     // Theta(1)     
    }    

    int randCandidateX = 0;// Theta(1)
    int randCandidateY = 0;// Theta(1)
    int randCandidate = 0;// Theta(1)

    // Lab 1 - do-while complexity analysis

    // Step 2: Generate another food object
    // Coordinate Generation
    // x [2, BoardX-3]
    // y [2, BoardY-3]   

    do
    {
        randCandidateX = rand() % (gmRef->getBoardSizeX() - 4) + 2;// Theta(1)
        randCandidateY = rand() % (gmRef->getBoardSizeY() - 4) + 2;// Theta(1)
    } while(bitVec[randCandidateX][randCandidateY] != 0); 
    // Best Case: Theta(1) - the first pair of generated x-y is a good candidate
    // Worst Case: Spent forever generating x-y pair, and always find itself colliding with player
    //  Theta(infinity)
    // Omega(1) = {Theta(1), Theta(n), Theta(n^2)....}

    undrawItem();  // Theta(1) 

    myItem->setX(randCandidateX);// Theta(1)
    myItem->setY(randCandidateY); // Theta(1)       

    // Prefix Generation
    // PF   [a-z, A-Z]
    randCandidate = rand() % 26 + 'A';  // 26 alpabets          // Theta(1)
    if(rand() % 2) randCandidate += 32; // randomly lowercased // Theta(1)
    myItem->setPF((char)randCandidate); // Theta(1)

    // Number Generation
    // Number [00, 99]
    myItem->setNum(rand() % 100);   // Theta(1)

    drawItem();// Theta(1)

    for(int i = 0; i < xsize; i++)// Theta(m)
        delete[] bitVec[i];// Theta(1)
    delete[] bitVec;// Theta(1)
}
//  T, exlucding do-while = Theta(n) OR Theta(m)
//  T, do-while = Omega(1)
//  T = Omega(1) ##   - unlikely, but still probable

objPos ItemBin::getItem()
{
    objPos temp(myItem->getX(), myItem->getY(), myItem->getNum(), myItem->getPF(), myItem->getSym());
    // constructor     // Theta(1)
    return temp;  // copy constructor     // Theta(1)
}    // Theta(1)
