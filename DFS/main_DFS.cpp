#include "Knight.h"
#include "knight.cpp"

/*
    Function header decloartions
*/
void startMenu();
int printMenu();

void partTwo();
void partFives();

int main()
{   

    startMenu();
    return 0;
}

void startMenu() 
{
    int userInput;
    while (true) 
    {
        userInput = printMenu();
        switch (userInput) 
        {
        case 1:
            partFives();
            break;
        case 2:
            cout << endl << "GoodBye..." << endl;
            return;

            break;
        default:
            cout << endl << "Invalid Input (1-5)" << endl;
        }
    
    }
}

int printMenu() 
{
    cout << "\n1. Start\n2. Quit\n";
    int userInput;
    cin >> userInput;
    return userInput;
}

void partFives() 
{
    int knight[2];
    int target[2];

    cout << "\nEnter Knight X Position: ";
    cin >> knight[0];
    cout << "\nEnter Knight Y Position: ";
    cin >> knight[1];
    cout << "\nEnter Target X Position: ";
    cin >> target[0];
    cout << "\nEnter Target Y Position: ";
    cin >> target[1];

    partFive(knight, target);
}