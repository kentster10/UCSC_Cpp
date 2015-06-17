//
//  HW1_Modified.cpp
//  UCSC_C++
//
//  Created by Ryan Kent on 2/16/15.
//
//
/* MAGIC SQUARE - An NxN matrix containing values from 1 to N*N that are
 ordered so that the sum of the rows, columns, and the major diagonals
 are all equal.  There is a particular algorithm for odd integers, and
 this program constructs that matrix, up to 13 rows and columns.  This
 program also adds the sums of the row, columns, and major diagonals.*/


#include <stdio.h>
#include <iostream>
#include <limits> //use operator numeric_limits (calls max limit fun within C++ compiler)
#include <cctype>  // use isdigit function

using namespace std;

class CMagic {
    private:
        int m_input, m_otherDiag;
        int **m_pnMatrix;
        bool m_goodInput;
    public:
        void Init();
        bool GetUserInput(int input);
        void MakeMagic();
        void DisplayMagic();
        void DeleteMagic();
};

int main()
{
    CMagic *ptrMatrix = new CMagic;
    int input = 0;
    cout << "\nMagic Squares: This program produces an NxN matrix where\n";
    cout << "N is some positive odd integer.  The matrix contains the\n";
    cout << "values 1 to N*N.  The sum of each row, each column, and\n";
    cout << "the two main diagonals are all equal.  Not only does this\n";
    cout << "program produces the matrix, it also computes the totals for\n";
    cout << "each row, column, and two main diagonals.\n";
    cout << "\nBecause of display constraints, this program can work with\n";
    cout << "values up to 13 only.\n";
    cout << "Enter a positive, odd integer, less than or equal to 13 (OR -1 to exit program):\n";
    while (cin >> input || !cin.eof()) {
        //check for exit condition
        if (input == -1){
            cout << "\nBye bye!\n";
            break;
        }
        if (ptrMatrix->GetUserInput(input))
        {
            ptrMatrix->Init();
            ptrMatrix->MakeMagic();
            ptrMatrix->DisplayMagic();
            ptrMatrix->DeleteMagic();
        }
            cout << "Enter a positive, odd integer, less than or equal to 13 (OR -1 to exit program):\n";
        }
    delete ptrMatrix;
}


bool CMagic::GetUserInput(int input)
{
    //Validity check for input:

    m_input = input;
    if (cin.good())
    {
        m_goodInput = true;
        if (m_input == 0 || m_input <=-2){
            cout << "Sorry, but the integer has to be positive.\n";
            m_goodInput = false;
        }
        else if (m_input > 13){
            cout << "Sorry, but the integer has to be less than 14.\n";
            m_goodInput = false;
        }
        else if (m_input%2 == 0) {
            cout << "Sorry, but the integer has to be odd.\n";
            m_goodInput = false;
        }
    }
    else if (!isdigit(m_input)) {
        cout << "Not a number\n";
        cin.clear();  // will reset the stream back to a good condition
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove all remaining junk from stream
        m_goodInput = false;
    }

    cin.clear();  // will reset the stream back to a good condition
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove all remaining junk from stream

        return m_goodInput;
}



void CMagic::Init()
{

    m_pnMatrix = new int*[m_input]; //memory allocation using new

    // initialize pointer array
    for (int row = 0; row <= m_input; row++){
        m_pnMatrix[row] = new int[m_input];
    }

    // initialize values of pointer array
    for (int row = 0; row <= m_input; row++){
        for (int col = 0; col <= m_input; col++){
            m_pnMatrix[row][col] = 0;
        }
    }


}

void CMagic::MakeMagic()
{
    //Loop for every value up to input*input, and position value in matrix
    int row = 1;
    int col = m_input/2 + 1;
    m_otherDiag = 0;


    for (int value = 1; value <= m_input*m_input; value++)
    {
        if (m_pnMatrix[row][col] > 0) // if some value present
        {
            row += 2;         // then move down one row
            if (row > m_input)   // if exceed side, then go to other side
                row -= m_input;

            col--;          // move left 1 column
            if (col < 1)    // if exceed side, then go to other side
                col = m_input;
        }

        m_pnMatrix[row][col] = value;  // assign value to location

        m_pnMatrix[0][col] += value;  // add its column total
        m_pnMatrix[row][0] += value;  // add to row total

        if (row == col){    // if it falls on diagonal
            m_pnMatrix[0][0] += value;  // add to diagnal total
        }

            if (row + col == m_input+1){  // add to other diagonal if it falls on line
                m_otherDiag += value;
            }

        row--;          // if row exceeds side then go to other side
        if (row < 1){
            row = m_input;
        }

        col++;          // if col exceeds side then go to other side
        if (col > m_input){
            col = 1;
        }

    }    
}

void CMagic::DisplayMagic()
{
    // print matrix totals
    cout << "\nThe number you selected was: " << m_input;
    cout << ", and the matrix is:\n\n";
    for (int row = 1; row <= m_input; row++)  /* Loop: print a row at a time*/
    {
        for (int col = 1; col <= m_input; col++)
        {
            cout.width(5);
            cout << m_pnMatrix[row][col];
        }
        cout << " =   " << m_pnMatrix[row][0] << "\n";
    }

    //   Print out the totals for each column, starting with diagonal total. */
    for (int col = 0; col <= m_input; col++)
        cout << "-----";                   //  value matrix and col totals

    cout << "\n" << m_otherDiag;                  // Print out the diagonal total

    for (int col = 1; col <= m_input; col++){
        cout.width(5);
        cout <<  m_pnMatrix[0][col];}         // Print out the column totals
    cout.width(5);
    cout << m_pnMatrix[0][0];                 // Print out the other diagonal
    cout << "\n";

}

void CMagic::DeleteMagic()
{
    // delete pointer from heap
    for (int row = 0; row <= m_input; row++)
        delete [] m_pnMatrix[row];
    delete [] m_pnMatrix;
}


