//
//  hw3.cpp
//  UCSC_C++
//
//  Created by Ryan Kent on 3/12/15.
//
///Apple LLVM version 6.0 (clang-600.0.57) (based on LLVM 3.5svn)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;


/********************************************************************
 *   CLASS NAME: CEmployee                                           *
 *   PURPOSE:
 *
 *   MEMBER FUNCTIONS:                                               *
 *     void Open (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr );
 *     void AddEmp (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr );
 *     void DeleteEmp (CEmployee *&pHeadPtr);
 *     void SearchEmp (CEmployee *pHeadPtr);
 *     void ListAllEmp (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr);
 *     void SaveToFile (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr);
 *     void ExitProg (CEmployee *pHeadPtr);                           *
 **********************************************************************/
class CEmployee {
public:
    void AddEmp (CEmployee *&pHeadPtr);
    void DeleteEmp (CEmployee *&pHeadPtr);
    void SearchEmp (CEmployee *&pHeadPtr);
    void ListAllEmp (CEmployee *&pHeadPtr);
    void SaveToFile (CEmployee *&pHeadPtr);
    void ExitProg (CEmployee *&pHeadPtr);
    int Open (CEmployee *&pHeadPtr, ifstream& InFile);
    
private:
    char m_Name [20];
    unsigned int m_Age;
    unsigned int m_Salary;
    CEmployee *m_pLink;
    CEmployee *pPrevious;
    void InsertEmp(CEmployee *&pHeadPtr, CEmployee *pNewAdd);
    string AddComma (CEmployee *&pHeadPtr);
    //string Open (CEmployee *&pHeadPtr);
    };

/********************************************************************
 *   FUNCTION: Open                                                  *
 *   PURPOSE:
 *
 *   PARAMETERS: pHeadPtr, pCurrPtr                                  *
 *   LOCAL VARIABLES: temp_name                                      *
 ********************************************************************/
int CEmployee::Open (CEmployee *&pHeadPtr, ifstream& InFile)
{


    char Str[80]; // string to be read from the file
    char d[] = ";"; //delimiter
    int i = 0;

    pHeadPtr = 0;
    while (InFile.getline(Str, 80)) {
        CEmployee *pCurrPtr = new CEmployee;
        //pCurrPtr->m_pLink = pHeadPtr;
        //pHeadPtr = pCurrPtr;

        strcpy(pCurrPtr->m_Name,strtok(Str, d));
        pCurrPtr->m_Age = atoi(strtok(NULL, d));
        pCurrPtr->m_Salary = atoi(strtok(NULL, d));

        pCurrPtr->InsertEmp(*&pHeadPtr, pCurrPtr);
        i++;
    } //while
    InFile.close();
    cout << endl << i << " employee records are loaded from the data file into the link list" << endl;
    return 0;

}

/***********************************************************************
 *   FUNCTION:  DeleteEmp                                               *
 *   PURPOSE:  Deletes employees from link list.                        *
 *   PARAMETERS:  pHeadPtr                                              *
 *   LOCAL VARIABLES: CurrPtr, LastPtr, Del_name                        *
 ***********************************************************************/
void CEmployee::DeleteEmp (CEmployee *&pHead)
{

    bool searchFound = false;
    static char caSearchName[20];
    cout << "\nEnter Employee Name to delete (First and Last): ";
    cin.getline(caSearchName,sizeof(caSearchName));
    cin.clear();

    cout << "you entered " << caSearchName << endl;

    CEmployee *pCurr, *pTemp;

    for (pCurr = pHead, pTemp = pHead; pCurr != NULL ; pTemp = pCurr, pCurr = pCurr->m_pLink ) //this works
        if (strcmp(pCurr->m_Name,caSearchName) == 0){
            cout << "search complete" << endl;

            cout << "Current Name: " << pCurr->m_Name << endl;
            cout << "Temp Name: " << pTemp->m_Name << endl;
            pTemp->m_pLink = pCurr->m_pLink;
            searchFound = true;
        }

    if (!searchFound) {
        cout << "Name Entered: " << caSearchName << " does not have a match" << endl;
    }

}

/***********************************************************************
 *   FUNCTION: SaveToFile                                               *
 *   PURPOSE: Saves data in link list to data file empinfo.data         *
 *   PARAMETERS: pHeadPtr, pCurrPtr                                     *
 *   LOCAL VARIABLES:  None                                             *
 ***********************************************************************/
void CEmployee::SaveToFile (CEmployee *&pHeadPtr)
{
    //CEmployee *loadFile = new CEmployee;

    enum userInput {y = 'y', n = 'n'};
    cout << "Would you like to save to existing file? (Y/N) {answering N will create a new file}" << endl;
    string input;
    getline(cin, input);
    cin.clear();
    //cin.ignore(1,'\n');

    if (input.length() != 1) {
        cout << "You must enter either Y or N" << endl;
    }
    char ch = input[0];
    char selectionLower = tolower(ch);
    string fname;

    switch (selectionLower) {
        case y:{
            fname = "empinfo.dat";
            ifstream InFile(fname);

            //Check if input file exists
            if (!InFile) {
                cout << "\nFile does not exist. Use Add and Save options to create file" << endl;
                //return;
            } //if
            break;
        }
        case n:{
            cout << "Enter Filename: " << endl;
            getline(cin, fname);
            break;
        }
    }

    ofstream Outfile(fname);


    if (!Outfile) {  // operator overloading: part ofstream class
        cout << "Cannot open output file.\n";
        return;
    }

    //write to file
    if (pHeadPtr != NULL)
    {
        while (pHeadPtr != NULL){
            Outfile << pHeadPtr->m_Name << "; " << pHeadPtr->m_Age << "; " <<  AddComma(pHeadPtr) << "\n";
            pHeadPtr = pHeadPtr->m_pLink;
        }
            Outfile.close();
    }
    else cout << "Need to add Employees before saving to file" << endl;

    return;


}

/***********************************************************************
 *   FUNCTION: AddEmp                                                   *
 *   PURPOSE:  Adds emmployees to link list.                            *
 *   PARAMETERS:  None                                                  *
 *   LOCAL VARIABLES:  None                                             *
 ***********************************************************************/
void CEmployee::AddEmp(CEmployee *&pHead)
{
    CEmployee *pNewAdd = new CEmployee;

    string input;

    cin.clear();
    //cin.ignore();

    cout << "\nEnter Employee Name: ";
    getline(cin, input);

    if(input[0] >= 'a' && input[0] <= 'z'){ // check for lower case input name
        input[0] = toupper(input[0]);
    }

    copy(input.begin(), input.end(), pNewAdd->m_Name);

    cout << "\nEnter Employee's Age: ";
    cin >> pNewAdd->m_Age;

    cout << "\nEnter Employee's Salary: ";
    cin >> pNewAdd->m_Salary;

    cout << "Current Head name: " << pHead->m_Name << endl;

    pNewAdd->InsertEmp(*&pHead, pNewAdd);
}

/**************************************************************
 * FUNCTION: Insert
 * PURPOSE: Inserts employee to link list and sorts
 *   PARAMETERS:  None                                                  *
 *   LOCAL VARIABLES:  None                                             *
 ***********************************************************************/
void CEmployee::InsertEmp(CEmployee *&pHead, CEmployee *pNewAdd)
{

    CEmployee *pTemp;

    if (pHead == NULL){
//        cout << "first name added" << endl;
        pHead = pNewAdd;
        return;
    }

    pTemp = pHead;

    if (strcmp(pTemp->m_Name, pNewAdd->m_Name) > 0) {
        pNewAdd->m_pLink = pTemp;
        pHead = pNewAdd;
//        cout << "head is greater than new thingy" << endl;
        return;
    }


    while (true)
    {
//        if (pTemp->m_pLink) {
//            cout << "checking new name " << pNewAdd->m_Name << " with current employee " << pTemp->m_pLink->m_Name << endl;
//        }
        if (pTemp->m_pLink == NULL || strcmp(pTemp->m_pLink->m_Name, pNewAdd->m_Name) > 0) {
            pNewAdd->m_pLink = pTemp->m_pLink;
            pTemp->m_pLink = pNewAdd;
            return;
        }
        pTemp = pTemp->m_pLink;
    }


}

/********************************************************************
 *  FUNCTION: ExitProg
 * PURPOSE: Exits program and deletes memory spaces that were being
 *        used.
 *  PARAMETERS: pHeadNode
 *   LOCAL VARIABLES:  pCurr, pDeleteThisNode
 ***********************************************************************/
void CEmployee::ExitProg (CEmployee *&pHeadNode)
{
    CEmployee *pCurr, *pDeleteThisNode;
    pCurr = pHeadNode;
    while (pCurr != 0)
    {
        pDeleteThisNode = pCurr;
        pCurr = pCurr->m_pLink;
        delete pDeleteThisNode;
    }
}

string CEmployee::AddComma (CEmployee *&pHeadPtr)
{
    string newSalary = to_string(pHeadPtr->m_Salary);

    if (pHeadPtr->m_Salary >= 1000)
    {
        int insertPosition = newSalary.length() - 3;

        while (insertPosition > 0) {
            newSalary.insert(insertPosition, ",");

            insertPosition-=3;
        }
    }
        return newSalary;

}

/*********************************************************************
 *   FUNCTION:  ListAllEmp                                            *
 *   PURPOSE:  Lists all employees in link list to the screen.        *
 *   PARAMETER:  pHeadPtr, pCurrPtr                                   *
 *   LOCAL VARIABLES: count                                           *
 **********************************************************************/
void CEmployee::ListAllEmp (CEmployee *&pHeadPtr)
{
    int num = 0;
    cout << left << setfill(' ');
    cout << "#" << '\t' << setw(22)  << "Employee Name" << setw(20) << "Age" << setw(7) << "Salary" <<  endl;
    cout << string(60, '=') << endl;

    CEmployee *pCurr = new CEmployee;
    pCurr = pHeadPtr;

    while (pCurr != NULL)
    {
        string newSalary = AddComma(pCurr);
        cout << ++num << "."  << '\t' << setw(22) << pCurr->m_Name << setw(20) << pCurr->m_Age << setw(7) << newSalary << endl;
        pCurr = pCurr->m_pLink;

    }

}

/*********************************************************************
 *   FUNCTION:  SearchEmp                                             *
 *   PURPOSE:  Searches link list for specified employee.             *
 *   PARAMTERS:  pHeadPtr                                             *
 *   LOCAL VARIABLES: CurrPtr, Search_name, flag                      *
 **********************************************************************/
void CEmployee::SearchEmp (CEmployee *&pHead)  // ex. 2-12 for searching
{
    bool searchFound = false;
    static char caSearchName[31];
    cout << "\nSearch Employee Name (First and Last): ";
    cin.getline(caSearchName,sizeof(caSearchName));
    cin.clear();

    CEmployee *pCurr, *pTemp;

    for (pCurr = pHead, pTemp = pHead; pCurr != NULL ; pTemp = pCurr, pCurr = pCurr->m_pLink )
        if (strcmp(caSearchName, pCurr->m_Name) == 0)  {
            cout << "Found Employee: " << pCurr->m_Name << endl;
            cout << "Employee Info: " << pCurr->m_Name << ", Age: " << pCurr->m_Age << ", Salary: " << AddComma(pCurr) << endl;

            pTemp->m_pLink = pCurr->m_pLink;
            searchFound = true;
        }

    if (!searchFound){
        cout << "Name Entered: " << pCurr->m_Name << ", was not found!" << endl;
    }
}


int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Usage: PR <filename>\n";
        return 1;
    }

    ifstream InFile(argv[1]);
    if (!InFile) {
        cout << "Cannot open file\n";
        return 1;
    }
    
    CEmployee *pHead;
    CEmployee *empList = new CEmployee;

    empList->CEmployee::Open(pHead,InFile);

    int input = -1;
    enum userInput {Add = 1, Delete, Search, List, Save, Exit};

    do
    {
        cout << "\nMenu Options:" << endl;
        cout << "\t" << "1. Add Employee" << endl;
        cout << "\t" << "2. Delete Employee" << endl;
        cout << "\t" << "3. Search Employee" << endl;
        cout << "\t" << "4. List All Employee" << endl;
        cout << "\t" << "5. Save Employee Database" << endl;
        cout << "\t" << "6. Exit Employee Database" << endl;
        cout << "Enter Your Choice:" << endl;

        cin >> input;

        if (cin.good()){
            if(input < 0) break;
        } //end if
        else if (!isdigit(input)) cout << "Not a number" << endl;

        cin.clear();
        cin.ignore(1,'\n');

        switch (input) {
            case Add:
                cout << "Add Employee" << endl;
                empList->AddEmp(pHead);
                break;
            case Delete:
                cout << "Delete Employee" << endl;
                empList->DeleteEmp(pHead);
                break;
            case Search:
                cout << "Search Employee" << endl;
                empList->SearchEmp(pHead);
                break;
            case List:
                cout << "List All Employee" << endl;
                empList->ListAllEmp(pHead);
                break;
            case Save:
                cout << "Save Employee Database" << endl;
                empList->SaveToFile(pHead);
                break;
            case Exit:
                cout << "Exit Employee Database" << endl;
                empList->ExitProg(pHead);
                break;
            default:
                break;
        }

    } while (input != Exit);

    return 0;

}