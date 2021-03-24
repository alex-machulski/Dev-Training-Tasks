#include <iostream>
#include <cstring>
#include <cstdlib>
#define AMOUNT_NUMBERS 100

using namespace std;
void clearString(char str[]);
bool isTwoOperationsInRow(char str[]);
bool isSpace(char str[]);
bool isWrongSymbols(char str[]);
bool isOnlyNumbers(char str[]);
bool isDividingByZero(char str[]);
bool isBracket(char str[]);
double multiplyAndDivision(char operations[], int numbers[AMOUNT_NUMBERS], double result);
double additionAndSubtraction(char operations[], int numbers[AMOUNT_NUMBERS], double result);

int main()
{
    char str[250]; // example "1+25/4-3/11";
    char operations[100], strTemp[10];
    int numbers[AMOUNT_NUMBERS] = { 0 }, lastOperation = 0;
    double result = 0.0, subResult = 0.0;
    // input validation
    while (true) {
        cout << "Enter math expression (without spaces): ";
        cin >> str;
        if (str[0] == '*' || str[0] == '/') {
            cout << "Math expression cannot start with '*' or '/'. Try again." << endl;
            continue;
        }
        else if (str[strlen(str) - 1] == '*' || str[strlen(str) - 1] == '/' || str[strlen(str) - 1] == '+' || str[strlen(str) - 1] == '-') {
            cout << "Math expression cannot end with '*', '/', '+' or '-'. Try again." << endl;
            continue;
        }
        else if (isTwoOperationsInRow(str)) {
            cout << "In mathematical expression cannot be 2 or more operations in a row. Try again." << endl;
            continue;
        }
        else if (isSpace(str)) {
            cout << "Mathematical expression must be without spaces. Try again." << endl;
            continue;
        }
        else if (isBracket(str)) {
            cout << "Sorry, but this calculator does not support brackets. Try again" << endl;
            continue;
        }
        else if (isWrongSymbols(str)) {
            cout << "Mathematical expression contains wrong characters. Try again." << endl;
            continue;
        }
        else if (isDividingByZero(str)) {
            cout << "Division by zero is prohibited. Try again." << endl;
            continue;
        }
        else
            break;
    }
    //parsing numbers and operations
    for (int i = 0, j = 0, k = 0, m = 0; i < strlen(str); i++) {
        if (i == 0 && (str[i] == '+' || str[0] == '-'))
            continue;
        if ((str[i] >= '0' && str[i] <= '9') || (j == 0 && str[i] == '-')) {
            strTemp[j] = str[i];
            j++;
        }
        if ((str[i] == '+') || (str[i] == '-' && j != 0) || (str[i] == '*') || (str[i] == '/') || (i == strlen(str) - 1)) {
            strTemp[j] = '\0';
            numbers[k] = atoi(strTemp);
            clearString(strTemp);
            k++;
            j = 0;
            if (i != strlen(str) - 1) {
                operations[m] = str[i];
                m++;
                lastOperation = m;
            }
            if (str[i] == '-') {
                strTemp[j] = str[i];
                j++;
            }
        }
    }
    if (str[0] == '-')
        numbers[0] = -numbers[0];
    operations[lastOperation] = '\0';
    // multiplication and division (first priority)
    subResult = multiplyAndDivision(operations, numbers, subResult);
    // addition and subtraction (second priority)
    result = additionAndSubtraction(operations, numbers, subResult);
    if (isOnlyNumbers(str) && strlen(operations) == 0)
        result = numbers[0];

    cout << "The result: " << result;

    return 0;
}

void clearString(char str[]) {
    for (int i = 0; i < strlen(str); i++)
        str[i] = ' ';
}

bool isTwoOperationsInRow(char str[]) {
    bool twoOperations = false;

    for (int i = 0; i < strlen(str) - 1; i++) {
        if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-') {
            if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '+' || str[i + 1] == '-') {
                twoOperations = true;
                break;
            }
        }
    }

    return twoOperations;
}

bool isSpace(char str[]) {
    bool space = false;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            space = true;
            break;
        }
    }

    return space;
}

bool isWrongSymbols(char str[]) {
    bool wrongSymbol = false;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < 42 || (str[i] > 43 && str[i] < 45) || (str[i] > 45 && str[i] < 47) || str[i] > 57)
            wrongSymbol = true;
        break;
    }

    return wrongSymbol;
}

bool isOnlyNumbers(char str[]) {
    bool onlyNumbers = true;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < 43 || (str[i] > 43 && str[i] < 45) || (str[i] > 45 && str[i] < 48) || str[i] > 57) {
            return false;
        }
    }

    return onlyNumbers;
}

bool isDividingByZero(char str[]) {
    for (int i = 0; i < strlen(str) - 1; i++) {
        if (str[i] == '/') {
            if (str[i + 1] == '0') {
                return true;
            }
        }
    }

    return false;
}

bool isBracket(char str[]) {
    bool bracket = false;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(' || str[i] == ')') {
            bracket = true;
            break;
        }
    }

    return bracket;
}

double multiplyAndDivision(char operations[], int numbers[AMOUNT_NUMBERS], double result) {
    double tempResult = 1.0;

    for (int i = 0; i < strlen(operations); i++) {
        if (i > 0) {
            // previous and next operations are NOT '*' or '/'
            if (operations[i] == '*' && (operations[i - 1] != '*' && operations[i - 1] != '/') && (operations[i + 1] != '*' && operations[i + 1] != '/')) {
                result = result + numbers[i] * numbers[i + 1];
            }
            else if (operations[i] == '/' && (operations[i - 1] != '*' && operations[i - 1] != '/') && (operations[i + 1] != '*' && operations[i + 1] != '/')) {
                result = result + 1.0 * numbers[i] / numbers[i + 1];
            }
            // previous operation is '*' or '/', next operation is NOT '*' or '/'
            else if (operations[i] == '*' && (operations[i - 1] == '*' || operations[i - 1] == '/') && (operations[i + 1] != '*' && operations[i + 1] != '/')) {
                result = result + tempResult * numbers[i + 1];
                tempResult = 1.0;
            }
            else if (operations[i] == '/' && (operations[i - 1] == '*' || operations[i - 1] == '/') && (operations[i + 1] != '*' && operations[i + 1] != '/')) {
                result = result + 1.0 * tempResult / numbers[i + 1];
                tempResult = 1.0;
            }
            // previous and next operations are '*' or '/'
            else if (operations[i] == '*' && (operations[i - 1] == '*' || operations[i - 1] == '/') && (operations[i + 1] == '*' || operations[i + 1] == '/')) {
                tempResult = tempResult * numbers[i + 1];
            }
            else if (operations[i] == '/' && (operations[i - 1] == '*' || operations[i - 1] == '/') && (operations[i + 1] == '*' || operations[i + 1] == '/')) {
                tempResult = 1.0 * tempResult / numbers[i + 1];
            }
            // previous operation is NOT '*' or '/', next operation is '*' or '/'
            else if (operations[i] == '*' && (operations[i - 1] != '*' && operations[i - 1] != '/') && (operations[i + 1] == '*' || operations[i + 1] == '/')) {
                tempResult = numbers[i] * numbers[i + 1];
            }
            else if (operations[i] == '/' && (operations[i - 1] != '*' && operations[i - 1] != '/') && (operations[i + 1] == '*' || operations[i + 1] == '/')) {
                tempResult = 1.0 * numbers[i] / numbers[i + 1];
            }
        }
        else {
            if (operations[i] == '*')
                result = result + numbers[i] * numbers[i + 1];
            else if (operations[i] == '/')
                result = result + 1.0 * numbers[i] / numbers[i + 1];
        }
    }

    return result;
}

double additionAndSubtraction(char operations[], int numbers[AMOUNT_NUMBERS], double result) {
    for (int i = 0; i < strlen(operations); i++) {
        if ((operations[i] == '+' || operations[i] == '-') && i == 0) {
            result = result + numbers[i];
        }
        if (operations[i] == '+' && operations[i + 1] != '*' && operations[i + 1] != '/') {
            result = result + numbers[i + 1];
        }
        else if (operations[i] == '-' && operations[i + 1] != '*' && operations[i + 1] != '/') {
            result = result + numbers[i + 1];
        }
    }

    return result;
}








