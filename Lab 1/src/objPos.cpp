#include "objPos.h"
#include <iostream>
using namespace std;

objPos::objPos()
{
    x = 0;
    y = 0;
    number = 0;
    prefix = 0;
    symbol = 0;

    reward = 0;
}

objPos::objPos(int xp, int yp, int num, char pref, char s)
{
    x = xp;   // Theta(1)
    y = yp;  // Theta(1)
    number = num;  // Theta(1)
    prefix = pref;  // Theta(1)
    symbol = s;  // Theta(1)

    reward = (number + prefix) * 3 / 2;
} // Theta(1)

objPos::objPos(const objPos& thisPos) // copy constructor
{
    x = thisPos.x; // Theta(1)
    y = thisPos.y; // Theta(1)
    number = thisPos.number; // Theta(1)
    prefix = thisPos.prefix; // Theta(1)
    symbol = thisPos.symbol; // Theta(1)

    reward = thisPos.reward;
} // Theta(1)

objPos& objPos::operator= (const objPos& thisPos)
{
    if(this != &thisPos)  // Theta(1)
    {
        x = thisPos.x;      // Theta(1)
        y = thisPos.y;      // Theta(1)
        number = thisPos.number;      // Theta(1)
        prefix = thisPos.prefix;      // Theta(1)
        symbol = thisPos.symbol;      // Theta(1)
        reward = thisPos.reward;
    }

    return *this;      // Theta(1)
}
// Theta(1)


int objPos::getX() const
{
    return x; // Theta(1)
}

int objPos::getY() const
{
    return y;// Theta(1)
}

int objPos::getNum() const
{
    return number;// Theta(1)
}

char objPos::getPF() const
{
    return prefix;// Theta(1)
}

char objPos::getSym() const
{
    return symbol;// Theta(1)
}

int objPos::getReward() const
{
    return reward;
}


void objPos::setX(int xp)
{
    x = xp;// Theta(1)
}

void objPos::setY(int yp)
{
    y = yp;// Theta(1)
}

void objPos::setNum(int num)
{
    number = num % 100;  // cap at two-digits// Theta(1)
}

void objPos::setPF(char pref)
{
    prefix = pref;// Theta(1)
}

void objPos::setSym(char sym)
{
    symbol = sym;// Theta(1)
}

void objPos::copyObjPos(objPos &thisPos)
{
    x = thisPos.x;
    y = thisPos.y;
    number = thisPos.number;
    prefix = thisPos.prefix;
    symbol = thisPos.symbol;
    reward = thisPos.reward;
}

bool objPos::isOverlap(const objPos* thisPos) const
{
    return (x == thisPos->getX() && y == thisPos->getY());  // Theta(1)
}// Theta(1)

void objPos::printObjPos() const
{
    cout << "(" << x << "," << y << "), " 
         << prefix << " " << number << " " << symbol << endl;
}


