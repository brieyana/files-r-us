/*
Author:     Brie Haynes
Compiler:   GNU GCC
Date:       12/6/2019

Purpose: This program creates student files where students will store their netID, major, classification,
and class information. Students can modify their file, display their file, and delete it, among many other
functions.
*/

// header files
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// signature(s)
void intro();
int readMajors(string MAJORS[], int size, int & trueSize);
bool validateMajors(string MAJORS[], int size, string major);
void studentInfo(string & netID, string & major, string & year, string MAJORS[], char prohibChars[], int size);
bool existingNetID(string netID);
void classInfo(int & hours, int & numClasses, string classNames[]);
void createFileName(string & fileName, string netID);
bool writeFile(string fileName, string netID, string major, string year, int hours, int numClasses, string classNames[]);
bool prohibitedChars(string prohibChars[], int size);
char accessSubMenu();
void modifyStudentInfo(string & major, string & year, string MAJORS[], int size);
void displayFile(string fileName);
bool checkProhibChars(string netID, char prohibChars[]);
void deleteFile(string fileName);
string renameFile(string  fileName, string netID);
void changeNetID(string & netID);

// change netID
void changeNetID(string & netID)
{
    system("cls");

    cout << "================================";
    cout << "\n\n\n" << setw(20) << "CHANGE NETID";
    cout << "\n\n\n================================\n\n";

    cout << "\nEnter your new netID:\n";
    cin >> netID;
    fflush(stdin);
}

// rename file
string renameFile(string fileName, string netID)
{
    string newName = netID + ".txt";
    rename(fileName.c_str(), newName.c_str());

    return newName;
}
void deleteFile(string fileName)
{
    remove(fileName.c_str());
}

// check for prohibited characters in netID
bool checkProhibChars(string netID, char prohibChars[])
{
    bool invalid = false;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (netID[i] == prohibChars[j])
            {
                invalid = true;
            }
        }
    }

    return invalid;
}

// display file
void displayFile(string fileName)
{
    ifstream fin;

    system("cls");

    cout << "================================";
    cout << "\n\n\n" << setw(22) << "DISPLAY FILE";
    cout << "\n\n\n================================\n\n";

    fin.open(fileName);

    cout << fin.rdbuf();

    fin.close();
}

void modifyStudentInfo(string & major, string & year, string MAJORS[], int size)
{
    system("cls");

    cout << "================================";
    cout << "\n\n\n" << setw(20) << "MODIFY FILE";
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

// sub menu for "access student file"
char accessSubMenu()
{
    char choice;

    system("cls");

    cout << "================================";
    cout << "\n\n\n" << setw(20) << "ACCESS FILE";
    cout << "\n\n\n================================";

    cout << "\n\n01. Modify File";
    cout << "\n02. Display File";
    cout << "\n03. Change netID";
    cout << "\n04. Back";
    cout << "\n\nPlease enter your choice (1 - 4): ";

    cin >> choice;
    fflush(stdin);

    return choice;
}

// find if netID already exists
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
        fout << "\n=====\n";
        fout << major;

        // classification
        fout << "\n\nClassification";
        fout << "\n==============\n";
        fout << year;

        fout << "\n\nNumber of classes";
        fout << "\n=================\n";
        fout << numClasses;

        fout << "\n\nCurrently taking\n";
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
void studentInfo(string & netID, string & major, string & year, string MAJORS[], char prohibChars[], int size)
{
    system("cls");

    cout << "================================";
    cout << "\n\n\n" << setw(25) << "STUDENT INFORMATION";
    cout << "\n\n\n================================";

    cout << "\n\nEnter your netID:\n";
    cin >> netID;
    fflush(stdin);

    // netID already exists
    while(existingNetID(netID))
    {
        cout << "\nThis file already exists. Please re-enter:\n";
        cin >> netID;
        fflush(stdin);
    }

    // invalid netID
    while (checkProhibChars(netID, prohibChars))
    {
        cout << "\nYour netID is invalid. Please re-enter:\n";
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
bool prohibitedChars(char prohibChars[], int size)
{
    ifstream chars;
    bool valid = false;

    chars.open("prohib.txt");

    if (!chars)
        chars.close();

    else
    {
        for (int i = 0; i < size && chars.good(); i++)
        {
            prohibChars[i] = chars.get();
        }

        valid = true;

        chars.close();
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
    // array size
    int trueSize;
    const int size = 50;

    // arrays
    string MAJORS[size];
    string classNames[size];
    char prohibChars[size] = {'\0'};

    // variables
    char choiceA, choiceB;
    int numClasses, creditHours;
    string netID, major, year, fileName;

    // introduction
    intro();
    cin.get();

    // START
    //*************************************// CATCHING ERRORS WITH FILES
    // read in majors
    if (readMajors(MAJORS, size, trueSize) == -1)
    {
        cout << "\nError with reading in majors from file\n";
        exit(0);
    }

    // read in prohibited characters
    if (!prohibitedChars(prohibChars, size))
    {
        cout << "\nError with reading in prohibited characters from file\n";
        exit(0);
    }
    //*************************************// CATCHING ERRORS WITH FILES

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
        cin >> choiceA;
        fflush(stdin);

        switch (choiceA)
        {
        // add file
        case '1':
            // get student information
            studentInfo(netID, major, year, MAJORS, prohibChars, trueSize);
            classInfo(creditHours, numClasses, classNames);

            // create name for file with netID
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

            // file does not exist
            if (!existingNetID(netID))
            {
                cout << "\nThis file does not exist.";
                cin.get();
            }

            // file exists
            else
            {
                // sub-menu for access
                do
                {
                    choiceB = accessSubMenu();

                    // modify student information
                    switch(choiceB)
                    {
                    case '1':
                        modifyStudentInfo(major, year, MAJORS, trueSize);
                        classInfo(creditHours, numClasses, classNames);
                        createFileName(fileName, netID);
                        writeFile(fileName, netID, major, year, creditHours, numClasses, classNames);
                        cout << "\nFile updated!";
                        cin.get();
                        break;

                    case '2':
                        createFileName(fileName, netID);
                        displayFile(fileName);
                        cin.get();
                        break;

                    case '3':
                        createFileName(fileName, netID);
                        changeNetID(netID);
                        fileName = renameFile(fileName, netID);
                        cout << "\nNetID updated!";
                        cin.get();
                        break;

                    case '4':
                        break;

                    default:
                        cout << "\nYour choice is invalid. Please re-enter.";
                        cin.get();
                        break;
                    }
                }
                while (choiceB != '4');
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
    while (choiceA != '4');


    return 0;
}
