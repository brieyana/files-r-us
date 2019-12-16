#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// signature(s)
void intro();
int readMajors(string MAJORS[], int size, int & trueSize);
bool validateMajors(string MAJORS[], int size, string major);
void studentInfo(string & netID, string & major, string & year, string MAJORS[], int size);
bool existingNetID(string netID);
void classInfo(int & hours, int & numClasses, string classNames[]);
void createFileName(string & fileName, string netID);
bool writeFile(string fileName, string netID, string major, string year, int hours, int numClasses, string classNames[]);
bool prohibitedChars(string prohibChars[], int size);
bool netIDFile(string netID);
void accessSubMenu(char & choice);
void modifyStudentInfo(string & major, string & year, string MAJORS[], int size);
void displayFile(string fileName);
void deleteFile(string fileName);
void renameFile(string fileName, string netID);
void changeNetID(string & netID);

void changeNetID(string & netID)
{
    system("cls");

    cout << "================================";
    cout << "\n\n\nCHANGE NETID";
    cout << "\n\n\n================================\n\n";

    cout << "Enter your new netID:\n";
    cin >> netID;
    fflush(stdin);
}

void renameFile(string fileName, string netID)
{
    string newName = netID + ".txt";
    rename(fileName.c_str(), newName.c_str());
}
void deleteFile(string fileName)
{
    remove(fileName.c_str());
}

/*
bool checkProhibChars()
{
    bool invalidNetID = false;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (netID[i] == prohibChars[j])
                invalidNetID = true;
        }
    }

    return invalidNetID;
}
*/

void displayFile(string fileName)
{
    ifstream fin;

    system("cls");

    cout << "================================";
    cout << "\n\n\nDISPLAY FILE";
    cout << "\n\n\n================================\n\n";

    fin.open(fileName);

    cout << fin.rdbuf();

    fin.close();
}
void modifyStudentInfo(string & major, string & year, string MAJORS[], int size)
{
    system("cls");

    cout << "================================";
    cout << "\n\n\nMODIFY FILE";
    cout << "\n\n\n================================";

    cout << "\nEnter your major:\n";
    getline(cin, major);
    fflush(stdin);

    while (!validateMajors(MAJORS, size, major))
    {
        cout << "\n\"" << major << "\" is not a valid major. Please re-enter:\n";
        getline(cin, major);
        fflush(stdin);
    }

    cout << "\nEnter your classification:\n";
    cin >> year;
    fflush(stdin);
}

void accessSubMenu(char & choice)
{
    system("cls");

    cout << "================================";
    cout << "\n\n\nACCESS FILE";
    cout << "\n\n\n================================";

    cout << "\n\n01. Modify File";
    cout << "\n02. Display File";
    cout << "\n03. Change netID";
    cout << "\n04. Back";
    cout << "\n\nPlease enter your choice (1 - 4): ";

    cin >> choice;
    fflush(stdin);
}

bool existingNetID(string netID)
{
    ifstream fin;
    bool exists = true;

    // converting netID to file name
    netID = netID + ".txt";

    fin.open(netID);

    if(!fin)
        exists = false;

    fin.close();

    return exists;
}

bool netIDFile(string netID)
{
    ofstream fout;
    bool wrote = true;

    fout.open("netIDs.txt", ios::app);

    if(!fout)
        wrote = false;

    else
        fout << netID << "\n";

    fout.close();

    return wrote;
}

// create student file
bool writeFile(string fileName, string netID, string major, string year, int hours, int numClasses, string classNames[])
{
    ofstream fout;
    bool wrote = true;

    fout.open(fileName);

    if (!fout)
        wrote = false;

    else
    {
        // netID
        fout << "NetID";
        fout << "\n=====\n";
        fout << netID;

        // major
        fout << "\n\nMajor";
        fout << "\n=====";
        fout << "\n" << major;

        // classification
        fout << "\n\nClassification";
        fout << "\n==============\n";
        fout << year;

        fout << "\n\nNumber of classes";
        fout << "\n=================\n";
        fout << numClasses;

        fout << "\n\nCurrently taking:\n";
        fout << "================\n";
        for (int i = 0; i < numClasses; i++)
        {
            fout << classNames[i] << "\n";
        }
    }

    fout.close();

    return wrote;
}

// create file name
void createFileName(string & fileName, string netID)
{
    fileName = netID + ".txt";
}

// get class information
void classInfo(int & hours, int & numClasses, string classNames[])
{
    system ("cls");

    cout << "================================";
    cout << "\n\n\n" << setw(27) << "CLASS INFORMATION";
    cout << "\n\n\n================================";

    cout << "\n\nEnter the amount of credit hours you are taking:\n";
    cin >> hours;
    fflush(stdin);

    cout << "\nEnter the number of classes you are taking:\n";
    cin >> numClasses;
    fflush(stdin);

    for (int i = 0; i < numClasses; i++)
    {
        cout << "\nEnter the name of class " << (i + 1) << ":\n";
        getline(cin, classNames[i]);
        fflush(stdin);
    }

}

// get student information
void studentInfo(string & netID, string & major, string & year, string MAJORS[], int size)
{
    system("cls");

    cout << "================================";
    cout << "\n\n\n" << setw(25) << "STUDENT INFORMATION";
    cout << "\n\n\n================================";

    cout << "\n\nEnter your netID:\n";
    cin >> netID;
    fflush(stdin);

    while(existingNetID(netID))
    {
        cout << "\nThis file already exists. Please re-enter:\n";
        cin >> netID;
        fflush(stdin);
    }

    cout << "\nEnter your major:\n";
    getline(cin, major);
    fflush(stdin);

    while (!validateMajors(MAJORS, size, major))
    {
        cout << "\n\"" << major << "\" is not a valid major. Please re-enter:\n";
        getline(cin, major);
        fflush(stdin);
    }

    cout << "\nEnter your classification:\n";
    cin >> year;
    fflush(stdin);
}

// validate majors
bool validateMajors(string MAJORS[], int size, string major)
{
    bool valid = false;

    for (int i = 0; i < size; i++)
    {
        if (major == MAJORS[i])
        {
            valid = true;
            break;
        }
    }

    return valid;
}

// prohibited characters
bool prohibitedChars(string prohibChars[], int size)
{
    ifstream fin;
    string line;
    bool valid = false;

    fin.open("prohib.txt");

    if (!fin)
        fin.close();

    else
    {
        for (int i = 0; i < size && fin.good(); i++)
        {
            getline(fin, prohibChars[i]);
        }

        valid = true;
    }

    return valid;
}

// read in majors
int readMajors(string MAJORS[], int size, int & trueSize)
{
    ifstream fin;
    string line;

    fin.open("majors.txt");

    if (!fin)
    {
        fin.close();
        return -1;
    }

    for (trueSize = 0; trueSize < size && fin.good(); trueSize++)
    {
        getline(fin, line);
        MAJORS[trueSize] = line;
    }

    return trueSize;
}

void intro()
{
    cout << "================================";
    cout << "\n\n\n\tSTUDENT FILES";
    cout << "\n\n\n================================";
    cout << "\n\nCreated by Brie Haynes";
    cout << "\nDate: 12/6/2019\n";
}

int main()
{
    // introduction
    intro();
    cin.get();

    // array size
    int trueSize;
    const int size = 50;

    // arrays
    string MAJORS[size];
    string netIDs[size];
    string classNames[size];
    string prohibChars[size];

    // variables
    char ch, ch2;
    int numClasses, creditHours;
    string netID, major, year, fileName;

    // START
    //*************************************// CATCHING ERRORS
    // read in majors
    if (readMajors(MAJORS, size, trueSize) == -1)
    {
        cout << "\nMAJORS ERROR\n";
        exit(0);
    }

    // read in prohibited characters
    if (!prohibitedChars(prohibChars, size))
    {
        cout << "\nPROHIBITED CHARS ERROR\n";
        exit(0);
    }
    //*************************************// CATCHING ERRORS

    do
    {
        system ("cls");

        cout << "================================";
        cout << "\n\n\n" << setw(20) << "MAIN MENU";
        cout << "\n\n\n================================";

        cout << "\n\n01. Add New Student File";
        cout << "\n02. Access Existing Student File";
        cout << "\n03. Delete Student File";
        cout << "\n04. Exit Program";
        cout << "\n\nPlease enter your choice (1 - 4): ";
        cin >> ch;
        fflush(stdin); // to flush input

        // c_str
        switch (ch)
        {
        // add file
        case '1':
            // get student information
            studentInfo(netID, major, year, MAJORS, size);

            // store netIDs into array for future file validation
            for (int i = 0; i < size; i++)
            {
                netIDs[i] = netID;
            }

            // add netIDs to a file
            if (!netIDFile(netID))
            {
                cout << "\nNetID file could not open.";
                cin.get();
                break;
            }

            classInfo(creditHours, numClasses, classNames);
            createFileName(fileName, netID);

            if (!writeFile(fileName, netID, major, year, creditHours, numClasses, classNames))
            {
                cout << "\nCould not write to file\n";
                cin.get();
            }
            else
            {
                cout << "\nFile created!";
                cin.get();
            }
            break;

        // access file
        case '2':
            cout << "\nEnter your netID: ";
            cin >> netID;
            fflush(stdin);

            if (!existingNetID(netID))
            {
                cout << "\nThis file does not exist.";
                cin.get();
            }

            // file exists
            else
            {
                // sub-menu for access
                while (true)
                {
                    accessSubMenu(ch2);

                    // modify student information
                    if (ch2 == '1')
                    {
                        modifyStudentInfo(major, year, MAJORS, size);
                        classInfo(creditHours, numClasses, classNames);
                        createFileName(fileName, netID);
                        writeFile(fileName, netID, major, year, creditHours, numClasses, classNames);
                        cout << "\nFile updated!";
                        cin.get();
                    }

                    if (ch2 == '2')
                    {
                        createFileName(fileName, netID);
                        displayFile(fileName);
                        cin.get();
                    }

                    if (ch2 == '3')
                    {
                        changeNetID(netID);
                        renameFile(fileName, netID);
                        cout << "\nNetID updated!";
                        cin.get();
                    }

                    if (ch2 == '4')
                        break;

                    else
                    {
                        cout << "\nInvalid choice";
                        cin.get();
                    }
                }
            }
            break;

        // delete file
        case '3':
            cout << "\nEnter your netID: ";
            cin >> netID;
            fflush(stdin);

            if (!existingNetID(netID))
            {
                cout << "\nThis file does not exist.";
                cin.get();
            }
            else
            {
                createFileName(fileName, netID);
                deleteFile(fileName);
                cout << "\nFile deleted!";
                cin.get();
            }
            break;

        // exit program
        case '4':
            break;

        // invalid choice
        default:
            cout << "\nYour choice is invalid. Please re-enter.";
            cin.get();
            break;
        }
    }
    while (ch != '4');

    return 0;
}
