//
//  hw2.cpp
//  UCSC_C++
//
//  Created by Ryan Kent on 3/2/15.
//
//

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdlib.h>




using namespace std;

#define MAXSIZE 5
class CarNode {

public:
    CarNode() : m_pNext(0), m_ticketNum(0) { }
    ~CarNode() {}
    CarNode(CarNode &) : m_pNext(0), m_ticketNum(0) { }

    // assign next pointer
    void SetNext(CarNode* p){m_pNext=p;}

    // assign ticket number
    void SetTicketNum(int tN){m_ticketNum=tN;}

    // get the next pointer
    CarNode *GetNext(void){return(m_pNext);}

    // get the ticket number
    int GetTicketNum(void){return(m_ticketNum);}

private:
    int m_ticketNum;    // ticket number of car
    CarNode *m_pNext;   // pointer to next node in stack

};

class CAlley {

public:
    CAlley () : m_pTop(0), mSize(0), mMaxSize(MAXSIZE) { }
    ~CAlley () {}
    CAlley (CAlley &) : m_pTop(0), mSize(0), mMaxSize(MAXSIZE) { }

    int Park(int);                          // park a car
    void Retrieve(int, CAlley *);           // retrieve a car
    int Terminate();               // quit the program
    string Display();                   // display contents af alley

    bool Empty(){return mSize==0;};      // check if stack is empty

    bool Full() {return ((mSize==MAXSIZE) ? true : false);}      // check if stack is full

    CarNode *GetTop(){return(m_pTop);};
    int Park(CarNode *);

    int CreateTicketNum() { return(mSize) ; };


private:

    void SetTop(CarNode *p){m_pTop=p;} // assign top pointer

    int Push(CarNode *);        // push one node onto top of stack

    CarNode * Pop();            // pop one node from the top of stack

    CarNode *m_pTop;            // pointer to top of Allay (stack)

    int mSize;                  // number of nodes in Allay (stack)
    int mMaxSize;               //max number of nodes in Allay (stack)


};




string CAlley::Display() 
{
    ostringstream result;
    CarNode *currentCar = GetTop();
    while (currentCar) {
        result << "\t" << currentCar->GetTicketNum();
        currentCar = currentCar->GetNext();
    }
    return result.str();


}

////////////////////////////////////////////////////////////////
// Function: CAlley::Push
// Purpose: Add a new node to top of stack
// Parameters:
// CarNode * pNewNode- the node to be added to top of stack
// Local Variables:
// status   - return 1 if pushed sucessfully
//          - return 0 if stack was full
//      (EX 3-3)
////////////////////////////////////////////////////////////////
int CAlley::Push(CarNode *pNewNode)
{
    if(Full()) {
        return 0;
    }
    if (Empty()) {
        pNewNode->SetNext(NULL);
    } else {
        pNewNode->SetNext(m_pTop);
    }
    m_pTop = pNewNode;
    //cout << "<debug> After push: " << Display() << "\n";
    ++mSize;
    return 1;

}

/////////////////////////////////////////////////////////////////
// Function: CAlley::Pop
// Purpose: Remove a node to top of Allay (stack).
// Parameters:
// CarNode * pNewNode- returns the node removed from top of Allay
//                      is zero if stack is empty
// Local Variables:
//  (EX 3-3)
/////////////////////////////////////////////////////////////////
CarNode * CAlley::Pop()
{

    if(!Empty()){
        CarNode *orig = m_pTop; //save top node to variable
        m_pTop = m_pTop->GetNext();
        mSize--;
        //cout << "<debug> After pop: " << Display() << "\n";
        return orig;
    }
    else {
        return  NULL;
    }

}


///////////////////////////////////////////////////////////////
// Function: CAlley::Park ( )
// Purpose: Park a car, if lot is not full. First allocate a
// node, then add it to the top of the stack
// Parameters:
//   userTicketNum  - the ticket number for the node to be added
// Local Variables:
//   CarNode *pNewNode   - local pointer to newly allocated node
//   int status          - 1 if parked sucessfully (lot not full)
//                          0 if not parked (log was full)
////////////////////////////////////////////////////////////////
int CAlley::Park(int userTicketNum)
{
    // create link in this function
        CarNode *pNewNode = new CarNode;
        pNewNode->SetTicketNum(userTicketNum);  // assign new node the input userTicketNum
        cout << "Ticket No.: " << pNewNode->GetTicketNum() << endl;
        return Push(pNewNode);
}


///////////////////////////////////////////////////////////////
// Function: CAlley:: Retrieve ( int userTicketNum, CAlley *pB)
// Purpose: Retrieve a car from alley A. Search for the car/node
// based on ticket num. by driving a car (popping off top) out of
// A and driving (pushing onto top) into B.
// If the car is found, it is not pushed onto B, but rather,
// it is deleted. Then the cars in B are moved back into A.
//
// Parameters:
//      userTicketNum: the ticket number for the node to be added
//      pB  - pointer to CAlley B
// Local Variables:
//      CarNode *pCurr: local pointer to newly allocated node
//      int found: 1 if car is found, 0 if not found
///////////////////////////////////////////////////////////////
void CAlley::Retrieve(int userTicketNum, CAlley *pB)
{
    if (userTicketNum > mSize) {
        cout << "CAR NOT PARKED IN MY LOT" << '\n';
        while (!this->Empty()){
            // pop from this->CAlley
            CarNode *topCar = this->Pop();
        }
    }

    // use pop here
    while (!this->Empty()){
        // pop from this->CAlley
        CarNode *topCar = this->Pop();

        cout << "<debug> This is the car ticket after pop: " << topCar->GetTicketNum() << endl;
        cout << "msize = " << mSize << endl;



        //check ticket number of CarNode == userTicketNum
        if (topCar->GetTicketNum() == userTicketNum) {

            while (!pB->Empty()){
                cout << "<debug> Enter while loop" << endl;
                CarNode *moveBack = pB->GetTop();
                this->Park(moveBack->GetTicketNum());
                delete moveBack;
            }

        continue;
        }
        else pB->Park(topCar->GetTicketNum());
            topCar = topCar->GetNext();





            //cout << "<debug> Car parked in B: " << topCar->GetTicketNum() << endl;

        delete topCar;
    }

    cout << "CAR NOT PARKED IN MY LOT" << '\n';

    //move cars in B back to A

}

int CAlley::Terminate()
{

    CarNode *pCurr, *pDeleteThisNode;

    pCurr = m_pTop; // assign address of head node to current node
    while (pCurr !=0){
        pDeleteThisNode = pCurr;
        delete pDeleteThisNode;
    }

    return 0;

}

int main()
{
    CAlley *AlleyA = new CAlley();
    CAlley *pAlleyB = new CAlley();
    CarNode *tesla = new CarNode;

    int ticketNumber = 1;
    int inputTicket = 0;
    enum userInput {d = 'd', p = 'p', r = 'r', q = 'q'};
    int status = 1;


    while (status) {
        cout << "D)isplay " << "\tP)ark " << "\tR)etrieve" << "\tQ)uit:";

        string input;
        getline(cin, input);

        if (input.length() != 1) {
            cout << "You must enter exactly one character\n";
            continue;
        }
        char ch = input[0];
        char selectionLower = tolower(ch);
        switch (selectionLower) {

            case d:
                cout << "Alley A:" << AlleyA->Display() << "\n";
                break;
            case p:
                AlleyA->Park(ticketNumber++);
                break;

            case r:
                int inputTicketNumber;
                cin >> inputTicket;
                    if (cin.good()){ // checks if state of stream is good for I/O operations
                        if (inputTicket < 0) break;
                        else cout << "Ticket No. = " <<  inputTicket << "\n";
                    } // end it
                    cin.clear();  // will reset the stream back to a good condition
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove all remaining junk from stream

                AlleyA->Retrieve(inputTicket, pAlleyB);
                break;
            case q:
                cout << "bye bye" << endl;
                status = AlleyA->Terminate();
                break;
            default:
                cout << "Invalid entry \n";
                break;
        }

    }
}
