#include "objPosDoubleHashing.h"
//#include "MacUILib.h"

#include <iostream>
using namespace std;

objPosDoubleHashing::objPosDoubleHashing()
{
    // Instantiate the objPos Hash Table of the default size TABLE_SIZE defined in the objPosHashTable abstract class
    // Should also initialize tableSize field with the default size TABLE_SIZE
    myHashTable=new objPos[TABLE_SIZE];
    tableSize= TABLE_SIZE;

    for (int i =0; i<tableSize; i++){
        myHashTable[i].setSym(0);
    }
    printMe();

}

objPosDoubleHashing::objPosDoubleHashing(int size)
{
    // Instantiate the objPos Hash Table of the specified size
    // Should also initialize tableSize field with specified size
    myHashTable= new objPos[size];
    tableSize=size;

    for (int i=0; i<tableSize; i++){
        myHashTable[i].setSym(0);
    }
}

objPosDoubleHashing::~objPosDoubleHashing()
{
    // delete the Hash Table
    delete[] myHashTable;
}

int objPosDoubleHashing::calculateHashing(int prefix, int number) const  // hashing function
{    
    // Implementing the primary hashing function

    // Add all the decimal integer digits of the Prefix ASCII char and the Number together

    // For example, given objPos.prefix = 'A' (65) and objPos.number = 98, then...
    //  h(x) = sum of all decimal digits of prefix and number = 6 + 5 + 9 + 8 = 28

    // return the sum as the hashing key. 
    int sum=0;
    sum+=prefix/10;
    sum+=prefix%10;

    sum+=number/10;
    sum+=number%10;

    return sum%tableSize;

}

int objPosDoubleHashing::calculateSecondaryHashing(int input) const
{
    // Implementing the secondary hashing function

    // 1. Sum up all digits of input
    // 2. return 5 - (sum mod 5)

    // e.g.  input = 18
    //       sum = 1 + 8 = 9
    //       return value = 5 - (9 % 5) = 5 - 4 = 1

    int sum=0;

    while (input>0){
        sum+=input%10;
        input/=10;
    }
    
    return 5-(sum%5);
}

bool objPosDoubleHashing::insert(const objPos &thisPos)
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    //  2. Check symbol field to see whether the indexed slot is empty
    //      If yes, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      Otherwise, proceed to collision resolution
    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    //  4. For every newly calculated key using quadratic probing, check for empty slot for insertion
    //      If empty slot is found, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      If element is already inserted, return false (indicating failed insertion)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)

    int key = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int h2=calculateSecondaryHashing(key);
    int i=0;

    while (i<MAX_PROBING_COUNT){
        int newKey=(key+i*h2) % tableSize;
        if (myHashTable[newKey].getSym()==0){
            myHashTable[newKey]=thisPos;
            myHashTable[newKey].setSym('v');
            return true;
        }
        i++;
    }
    return false;
}

bool objPosDoubleHashing::remove(const objPos &thisPos)  // lazy delete 
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    //  2. Check if the data at the slot matches thisPos (prefix and number)
    //      If yes, perform lazy delete by setting symbol to 0, then return true (indicating successful removal)
    //      Otherwise, proceed to collision resolution
    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    //  4. For every newly calculated key using quadratic probing, check for data matching (identical prefix and number)
    //      If match found, perform lazy delete by setting symbol to 0, then return true (indicating successful removal)
    //      If empty slot encountered, the probing chain reaches the end, hence return false (indicating failed removal)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)

    int key =calculateHashing(thisPos.getPF(), thisPos.getNum());
    
    int i=0;

    while (i<MAX_PROBING_COUNT){
       
        if (myHashTable[key].getPF()==thisPos.getPF() && 
            myHashTable[key].getNum()==thisPos.getNum() &&
            myHashTable[key].getSym()=='v')
            {
                myHashTable[key].setSym('\0');   //lazy delete
                return true;
            }
        if (myHashTable[key].getSym()=='\0'){
            return false;
        }
        int h2=calculateSecondaryHashing(key);
        key=(key+i*h2) % tableSize;
        i++;
    }
    return false;

}

bool objPosDoubleHashing::isInTable(const objPos &thisPos) const
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    //  2. Check if the data at the slot matches thisPos (prefix and number) 
    //      If matched, further chech whether symbol != 0 (data not deleted yet)
    //          If yes, return true (indicating successfully found)
    //          Otherwise, return false (indicating failed to find)
    //     If no match is found, proceed to collision resolution
    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    //  4. For every newly calculated key using quadratic probing, check for data matching (identical prefix and number)
    //      If matched, further chech whether symbol != 0 (data not deleted yet)
    //          If yes, return true (indicating successfully found)
    //          Otherwise, return false (indicating failed to find)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)

    int key=calculateHashing(thisPos.getPF(), thisPos.getNum());
    int h2= calculateSecondaryHashing(key);
    int i=0;

    while (i<MAX_PROBING_COUNT){
        int newKey=(key+i*h2)%tableSize;
        if (myHashTable[newKey].getPF()==thisPos.getPF() &&
            myHashTable[newKey].getNum()==thisPos.getNum() && 
            myHashTable[newKey].getSym() == 'v'){
                return true;
            }
        if (myHashTable[newKey].getSym()==0){
            return false;
        }    
        i++;
    }
    return false;



}

double objPosDoubleHashing::getLambda() const
{
    // Calculate the Load Factor of the Hash Table
    // Check lecture code for examples

    int occupied=0;
    for (int i =0; i<TABLE_SIZE; i++)
    {
        if (myHashTable[i].getSym()!=0){
            occupied++;
        }
    }
    return (1.0*occupied)/TABLE_SIZE;
}

void objPosDoubleHashing::printMe() const
{
    // Recommended Format:
    //  [Key] Prefix Number  Symbol

    // e.g. ...
    //      [20] A 9  v
    //      [21] 0 
    //      [22] E 7  v
    //      ... 
 


    // Provided Code for Model Code Integration
    ////////////////////////////////////////////////

    // MacUILib_printf("[ ");
    // for(int i = 0; i < TABLE_SIZE; i++)
    // {
    //     if(myHashTable[i].getSym() != 0)
    //         MacUILib_printf("%c%d ", myHashTable[i].getPF(), myHashTable[i].getNum());     
    // }
    // MacUILib_printf("] L=%.2f", getLambda());

    // You will also need to #include "MacUILib.h" when integrating with the model code.

    for (int i=0; i<tableSize; i++){
        cout<< "[" << i << "]";
        if (myHashTable[i].getSym()!=0){
            cout << myHashTable[i].getPF() << " " << myHashTable[i].getNum() << " " << myHashTable[i].getSym();
        }
        cout << endl;
    }
}