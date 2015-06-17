//
//  hw4.cpp
//  UCSC_C++
//
//  Created by Ryan Kent on 3/30/15.
//
// Apple LLVM version 7.0.0 (clang-700.0.9) (based on LLVM 3.7.0svn)

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

// This data structure should be a record in a input file
struct AirFile {
    int Type;
    char Name[17];
    int nTotalPassenger;
    int nTotalWeight;
    int Propellant;
    int Range;
};
enum AirShipType {AIRPLANE, BALLOON};
enum EngineType {JET, PROPELLER};

class CAirVehicle {
    public:
        CAirVehicle() { }
        virtual void GetData(AirFile &data) = 0;
        virtual void ShowData() = 0;
        AirShipType GetAirshipType() {return m_AirshipType;}
    protected:
        AirShipType m_AirshipType;
};

class CAirplane : public CAirVehicle {
public:
    CAirplane() : CAirVehicle() {}
    //enum EngineType {JET, PROPELLER};
    void GetData(AirFile &data);
    void ShowData();
    const char *SetEngineType(EngineType Engine);
private:
    int m_Range;
    //int m_Engine;
    char m_Name[17];
    EngineType m_Engine;
};

const char *CAirplane::SetEngineType(EngineType Engine)
{
    switch (Engine) {
        case JET:
            return "Jet";
            break;
        case PROPELLER:
            return "Propeller";
            break;
        default:
            return "No Engine Type";
            break;
    } //end switch
}


// Function: GetData
void CAirplane::GetData(AirFile &data)
{
    // cast integer to enum
    m_AirshipType = AirShipType(data.Type);
    m_Engine = EngineType(data.Propellant);
    strcpy(m_Name, data.Name);
    m_Range = data.Range;
}

void CAirplane::ShowData()
{
    cout << setw(20) << left << m_Name << setw(12) << SetEngineType(m_Engine) << setw(10) << m_Range << endl;
}

class CBalloon : public CAirVehicle {
public:
    CBalloon() : CAirVehicle() {}
    enum GasType {HELIUM, HYDROGEN};
    void GetData(AirFile &data);
    void ShowData();
    const char *SetGasType(GasType Gas);

private:
    //int m_Gas;
    int m_Range;
    char m_Name[17];
    GasType m_Gas;
};

const char *CBalloon::SetGasType(GasType Gas)
{
    switch (Gas) {
        case HELIUM:
            return "helium";
            break;
        case HYDROGEN:
            return "hydrogen";
            break;
        default:
            return "No Engine Type";
            break;
    } //end switch
}

void CBalloon::GetData(AirFile &data)
{
    // cast integer to enum
    m_AirshipType = AirShipType(data.Type);
    m_Gas = GasType(data.Propellant);
    strcpy(m_Name, data.Name);
    m_Range = data.Range;
}
void CBalloon::ShowData()
{
    cout << setw(20) << left << m_Name << setw(12) << SetGasType(m_Gas) << setw(10)<< m_Range << endl;
}

// Airplane = 0
// Ballon = 1
int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: PR <filename>\n";
        return 1;
    }

    ifstream Infile(argv[1]);
    if (!Infile) {
        cout << "Cannot open file\n";
        return 1;
    }

    char LineBuf[100];
    char d[] = ",";

    CAirVehicle *pAirVehicle[10];
    int i=0;
    do{
        Infile.getline(LineBuf, 100);

        struct AirFile data;

        int typeCheck = atoi (strtok(LineBuf, d));

        switch (typeCheck) {
            case AIRPLANE:
                // Create Airplane Object
                pAirVehicle[i] = new CAirplane();
                data.Type = typeCheck;
                strcpy(data.Name,strtok(NULL, d));
                data.nTotalPassenger = atoi (strtok(NULL, d));
                data.nTotalWeight = atoi (strtok(NULL, d));
                data.Propellant = atoi (strtok(NULL, d));
                data.Range = atoi (strtok(NULL, d));
                break;
            case BALLOON:
                // Create Balloon Object
                pAirVehicle[i] = new CBalloon();
                data.Type = typeCheck;
                strcpy(data.Name ,strtok(NULL, d));
                data.nTotalPassenger = atoi (strtok(NULL, d));
                data.nTotalWeight = atoi (strtok(NULL, d));
                data.Propellant = atoi (strtok(NULL, d));
                data.Range = atoi (strtok(NULL, d));
                break;
            default:
                break;
        }// end switch

        // call appropriate function
        pAirVehicle[i++]->GetData(data);
        memset(LineBuf,'\0',100);
    } while (!Infile.eof());

    cout << "List of all Airplanes\n";
    cout << "Name" << "\t\t   Engine Type";
    cout << "\tMaximum Range" << "\n";
    cout << string(47, '=') << endl;

    for (int i = 0; i < 10; i++) {
        if (pAirVehicle[i]->GetAirshipType() == AIRPLANE)
        {
            pAirVehicle[i]->ShowData();
        }
    }

    cout << "\n\nList of all Balloons\n";
    cout << "Name" << "\t\t   Gas Type";
    cout << "\tMaximum Altitude" << "\n";
    cout << string(50, '=') << endl;

    for (int i = 0; i < 10; i++) {
        if (pAirVehicle[i]->GetAirshipType() == BALLOON)
        {
            pAirVehicle[i]->ShowData();
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (pAirVehicle[i])
        {
            delete pAirVehicle[i];// Delete appropriate object
        }
    } // end for loop

    return 0;
}
