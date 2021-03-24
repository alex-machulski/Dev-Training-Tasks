#include <iostream>

using namespace std;

#define PIN_CODE 1234
#define ESPRESSO_PRICE 2.00
#define CAPPUCCINO_PRICE 2.50
#define LATTE_PRICE 3.00
#define MIN_VALUE_BYN 1.00
#define MAX_VALUE_BYN 100.00
#define MIN_CUPS_ORDER 1
#define MAX_CUPS_ORDER 9

double userBalance = 0.0, coffeeMachineBalance = 0.0, clientMoney = 0.0;
int totalCups = 7;

void printMainMenu();
void printServiceMenu();
double checkUserBalance();
double insertMoney();
int makeEspresso(int neededCups);
int makeCappuccino(int neededCups);
int makeLatte(int neededCups);
bool isEnoughMoney(int neededCups, double price, double userBalance);
bool isEnoughCups(int neededCups, int totalCups);
void checkPIN();
void checkCoffeeMachineBalance(double balance);
void checkRemainingCoffeeCups(int number);
void withdrawCash(double balance);

int main()
{
    int userChoice = 0, neededCups = 0;

    while (true) {       
        cout << endl << "LEI700 Main Menu" << endl;
        cout << "Current balance: " << checkUserBalance() << " BYN" << endl;
        printMainMenu();
        cout << "Your choice? ";
        cin >> userChoice;
        if (userChoice == 1) {
            clientMoney = insertMoney();
        }
        else if (userChoice == 2) {
            cout << "How many cups of espresso do you want (from " << MIN_CUPS_ORDER << " to " << MAX_CUPS_ORDER << ")? ";
            cin >> neededCups;
            if (neededCups < MIN_CUPS_ORDER || neededCups > MAX_CUPS_ORDER) {               
                cout << "Incorrect number of cups. Try again." << endl;
                continue;
            }
            int readyEspresso = makeEspresso(neededCups);
            if (readyEspresso == -1) {            
                cout << "Sorry, the coffee cups are not enough. Please, call the service center EspressoBiancci." << endl;
            }
            else if (readyEspresso == -2) {               
                cout << "Not enough money to pay for your order" << endl;
            }
            else {
                userBalance -= readyEspresso * ESPRESSO_PRICE;
                coffeeMachineBalance += readyEspresso * ESPRESSO_PRICE;
                totalCups -= readyEspresso;               
                cout << "Take your " << readyEspresso << " cup(-s) of espresso!" << endl;
            }
        }
        else if (userChoice == 3) {
            cout << "How many cups of cappuccino do you want? (from " << MIN_CUPS_ORDER << " to " << MAX_CUPS_ORDER << ")? ";
            cin >> neededCups;
            if (neededCups < MIN_CUPS_ORDER || neededCups > MAX_CUPS_ORDER) {              
                cout << "Incorrect number of cups. Try again." << endl;
                continue;
            }
            int readyCappuccino = makeCappuccino(neededCups);
            if (readyCappuccino == -1) {              
                cout << "Sorry, the coffee cups are not enough. Please, call the service center EspressoBiancci." << endl;                
            }
            else if (readyCappuccino == -2) {            
                cout << "Not enough money to pay for your order" << endl;
            }
            else {
                userBalance -= readyCappuccino * CAPPUCCINO_PRICE;
                coffeeMachineBalance += readyCappuccino * CAPPUCCINO_PRICE;
                totalCups -= readyCappuccino;           
                cout << "Take your " << readyCappuccino << " cup(-s) of cappuccino!" << endl;
            }
        }
        else if (userChoice == 4) {
            cout << "How many cups of latte do you want? ";
            cin >> neededCups;
            if (neededCups < MIN_CUPS_ORDER || neededCups > MAX_CUPS_ORDER) {           
                cout << "Incorrect number of cups. Try again." << endl;
                continue;
            }
            int readyLatte = makeLatte(neededCups);
            if (readyLatte == -1) {               
                cout << "Sorry, the coffee cups are not enough. Please, call the service center EspressoBiancci." << endl;
            }
            else if (readyLatte == -2) {              
                cout << "Not enough money to pay for your order" << endl;
            }
            else {
                userBalance -= readyLatte * LATTE_PRICE;
                coffeeMachineBalance += readyLatte * LATTE_PRICE;
                totalCups -= readyLatte;      
                cout << "Take your " << readyLatte << " cup(-s) of latte!" << endl;
            }
        }
        else if (userChoice == 0) {
            checkPIN();
            coffeeMachineBalance += userBalance;
            userBalance = 0.0;
            while (true) {
                printServiceMenu();
                cout << "Your choice? ";
                cin >> userChoice;
                if (userChoice == 1)
                    checkCoffeeMachineBalance(coffeeMachineBalance);
                else if (userChoice == 2)
                    checkRemainingCoffeeCups(totalCups);
                else if (userChoice == 3) {
                    withdrawCash(coffeeMachineBalance);
                    coffeeMachineBalance = 0.0;
                }
                else if (userChoice == 4) {                  
                    cout << "Returning to main menu." << endl;
                    break;
                }
                else
                    cout << "Choose 1...4, please!" << endl;
            }
        }
        else
            cout << "Choose 0...4, please!" << endl;
    }
    return 0;
}

void printMainMenu() {
    cout << "1. Insert money" << endl;
    cout << "2. Make espresso (" << ESPRESSO_PRICE << " BYN)" << endl;
    cout << "3. Make cappuccino (" << CAPPUCCINO_PRICE << " BYN)" << endl;
    cout << "4. Make latte (" << LATTE_PRICE << " BYN)" << endl;
    cout << "0. Service" << endl;
}

void printServiceMenu() {
    cout << endl << "LEI700 Service Menu" << endl;
    cout << "1. Check coffee machine balance" << endl;
    cout << "2. Check remaining coffee cups" << endl;
    cout << "3. Withdraw cash" << endl;
    cout << "4. Return to main menu" << endl;
}

double checkUserBalance() {
    userBalance += clientMoney;
    clientMoney = 0.0;
    return userBalance;
}

double insertMoney() {
    double money = 0.0;

    while (true) {
        cout << "Insert your money (from " << MIN_VALUE_BYN << " to " << MAX_VALUE_BYN << "): ";
        cin >> money;
        if (money >= MIN_VALUE_BYN && money <= MAX_VALUE_BYN)
            break;
        else {
            cout << "Wrong amount of money" << endl;
            continue;
        }
    }
    cout << "Your balance has been increased by " << money << " BYN" << endl;
    return money;
}

bool isEnoughMoney(int neededCups, double price, double userBalance) {
    return (neededCups * price <= userBalance) ? true : false;
}

bool isEnoughCups(int neededCups, int totalCups) {
    return (neededCups <= totalCups) ? true : false;
}

int makeEspresso(int neededCups) {
    int result;

    if (!isEnoughCups(neededCups, totalCups))
        result = -1;
    else if (!isEnoughMoney(neededCups, ESPRESSO_PRICE, userBalance))
        result = -2;
    else
        result = neededCups;
    return result;
}

int makeCappuccino(int neededCups) {
    int result;

    if (!isEnoughCups(neededCups, totalCups))
        result = -1;
    else if (!isEnoughMoney(neededCups, CAPPUCCINO_PRICE, userBalance))
        result = -2;
    else
        result = neededCups;
    return result;
}

int makeLatte(int neededCups) {
    int result;

    if (!isEnoughCups(neededCups, totalCups))
        result = -1;
    else if (!isEnoughMoney(neededCups, LATTE_PRICE, userBalance))
        result = -2;
    else
        result = neededCups;
    return result;
}

void checkPIN() {
    int numOfAttempts = 3, userPin = 0;

    while (true) {
        if (numOfAttempts == 0) {
            cout << "You entered the wrong PIN code 3 times. The coffee machine is blocked. Contact EspressoBiancci." << endl;
            while (true)
            {
            }
        }
        cout << "Enter the four-digit PIN (" << numOfAttempts << " attempts left): ";
        cin >> userPin;
        if (userPin == PIN_CODE)
            break;
        else {
            cout << "Wrong PIN." << endl;
            numOfAttempts--;
        }
    }
}

void checkCoffeeMachineBalance(double balance) {
    cout << "Coffee machine balance: " << balance << " BYN" << endl;
}

void checkRemainingCoffeeCups(int number) {
    cout << "Remaining coffee cups: " << number << endl;
}

void withdrawCash(double balance) {
    if (balance == 0) {
        cout << "All cash withdrawn. Coffee machine balance: " << balance << " BYN" << endl;
    }
    else {
        cout << "The sum of cash withdrawal: " << balance << " BYN" << endl;
        balance = 0.0;
    }
}




