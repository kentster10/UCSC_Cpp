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


using namespace std;

#define MAXSIZE 5
class CarNode {

public:
    CarNode() : m_pNext(0), m_ticketNum(0) { };
    ~CarNode();
    CarNode(CarNode &) : m_pNext(0), m_ticketNum(0) { };

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
    void Terminate();               // quit the program
    void Display(char *);                   // display contents af alley

    bool Empty(){return mSize==0;};      // check if stack is empty

    bool Full() {return ((mSize==MAXSIZE) ? true : false);}      // check if stack is full

    CarNode *GetTop(){return(m_pTop);};
    int Park(CarNode *);

    int CreateTicketNum() { return(mSize) ; };



private:

    void SetTop(CarNode *p){m_pTop=p;} // assign top pointer

    //bool Empty(){return ((mSize==0) ? true : false);}

    int Push(CarNode *);        // push one node onto top of stack

    CarNode * Pop();            // pop one node from the top of stack

    CarNode *m_pTop;            // pointer to top of Allay (stack)

    int mSize;                  // number of nodes in Allay (stack)
    int mMaxSize;               //max number of nodes in Allay (stack)


};


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
    if(!Full()) {
        m_pTop = pNewNode;
        ++mSize;
        return 1;
    }
    else {
        return 0;
    }

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
    if (!Full()){
        CarNode *pNewNode = new CarNode;
        pNewNode->SetTicketNum(userTicketNum);  // assign new node the input userTicketNum
        Push(pNewNode);
        cout << "Ticket no. = " << userTicketNum << '\n';
        return 1;
    }
    return 0;
}

/*
int CAlley::Park(CarNode *pUserCar)
{
    if (!Full()){
        Push(pUserCar);
        return 1;
    }
    return 0;
}
*/



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
    // use pop here

    while (!this->Empty()){
        // pop from this->CAlley
        //CarNode *leaf = Pop();

        topCar = this->CarNode *GetTop()

        //check ticket number of CarNode == userTicketNum
        if (topCar->GetTicketNum() == userTicketNum) {
        cout << "Ticket no. = " << userTicketNum << '\n';
        break;
        }

        if (topCar->GetTicketNum() > mSize) cout << "CAR NOT PARKED IN MY LOT" << '\n';

        else pB->Park(topCar->GetTicketNum());
        delete topCar;
    }
    //move cars in B back to A
    while (!pB->Empty()){
        CarNode *moveBack = pB->GetTop();
        this->Park(moveBack->GetTicketNum());
        delete moveBack;
    }

}

void CAlley::Terminate()
{
    /*
    CarNode *pCurr, *pDeleteThisNode;

    pCurr = m_pTop; // assign address of head node to current node
    while (pCurr !=0){
        pDeleteThisNode = pCurr;
        delete pDeleteThisNode;

    }
     */
}

int main()
{
    CAlley AlleyA;
    CAlley *pAlleyB;
    CarNode *tesla = new CarNode;


    enum userInput {d = 'd', p = 'p', r = 'r', q = 'q'};

    cout << "D)isplay " << "\tP)ark " << "\tR)etrieve" << "\tQ)uit:" << '\n';

    string input = "";
    //char selection  = {0};
    while (cin >> input || !cin.eof()) {
        //check for exit condition
        cout << "Please enter 1 char (d, p, r, or q): ";
        cin >> input;

        if (input.length() == 1) {
            //string selection = &input[0];
            char selectionLower = tolower(input[0]);
            //userInput select = selectionLower;

            switch (selectionLower) {
                case d:
                    //DisplayFun
                    cout << "Alley A: " << '\t';
                    while (!AlleyA.Empty()){
                         cout << tesla->GetTicketNum()  << '\t';
                    }
                    cout << '\n';

                    break;

                case p:
                    //ParkFun

                    if ( AlleyA.Full() ) {
                        cout << "PARKING LOT FULL" << '\n';
                    }
                    else {
                        int curTicket = AlleyA.CreateTicketNum();
                        AlleyA.Park(curTicket);
                    }
                    break;

                case r:
                    //RetrieveFun
                    AlleyA.Retrieve(tesla->GetTicketNum(), pAlleyB);

                    break;

                case q:
                    //TerminalFun
                    AlleyA.Terminate();


                default:
                    cerr << "Invalid Entry\n";
                    break;
            }

            break;
        }

        cout << "Invalid character, please try again" << endl;
    }
    cout << "D)isplay " << "\tP)ark " << "\tR)etrieve" << "\tQ)uit:" << '\n';

    //return 0;

}
