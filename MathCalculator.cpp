#include <iostream>
#include <stdlib.h>
#define N 10
#define CELL '*'
#define EMPTY ' '

using namespace std;
char getRandomCell();
void fillTheFields(char arr[][N], int matrixSide);
void printLifeBoard(char arr[][N], int matrixSide);
void copyArray(char fromArray[][N], char toArray[][N], int matrixSide);
int checkLivingCellsAround(char arr[N][N], int matrixSide, int i, int j);
int correctXY(int coordinate, int matrixSide);
void getGenerationChange(char arr[][N], char tempArr[][N], int matrixSide);
bool isCellsOnMatrix(char arr[][N], int matrixSide);
bool isGenerationChanged(char arr[][N], char tempArr[][N], int matrixSide);

char life[N][N], tempLife[N][N];
int livingCells = 0, numberOfGenerations = 0, generationCounter = 0;

int main()
{
    cout << "This is Conway's Game of Life" << endl;
    while (true) {
        cout << "Enter the number of generations (number > 0): ";
        cin >> numberOfGenerations;
        if (numberOfGenerations < 1) {
            cout << "Wrong number, try again." << endl << endl;
        }
        else
            break;
    }
    cout << "The game started!" << endl;
    fillTheFields(life, N);
    while (numberOfGenerations >= 0) {
        system("clear");
        cout << generationCounter << " generation: " << endl;
        printLifeBoard(life, N);
        getchar();
        copyArray(life, tempLife, N);
        getGenerationChange(life, tempLife, N);
        if (!(isCellsOnMatrix(life, N)))
            break;
        if (!(isGenerationChanged(life, tempLife, N)))
            break;
        generationCounter++;
        numberOfGenerations--;
    }

    return 0;
}

char getRandomCell() {
    char cell;

    int x = rand() % 2;
    if (x == 0)
        cell = EMPTY;
    else
        cell = CELL;

    return cell;
}

void fillTheFields(char arr[][N], int matrixSide) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            arr[i][j] = EMPTY;
    }
    arr[4][4] = CELL;
    arr[5][5] = CELL;
    arr[6][3] = CELL;
    arr[6][4] = CELL;
    arr[6][5] = CELL;
}

void printLifeBoard(char arr[][N], int matrixSide) {
    for (int i = 0; i < matrixSide; i++) {
        for (int j = 0; j < matrixSide; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void copyArray(char fromArray[][N], char toArray[][N], int matrixSide) {
    for (int i = 0; i < matrixSide; i++) {
        for (int j = 0; j < matrixSide; j++) {
            toArray[i][j] = fromArray[i][j];
        }
    }
}

int checkLivingCellsAround(char arr[N][N], int matrixSide, int i, int j) {
    int result = 0;

    if (arr[correctXY(i, matrixSide)][correctXY(j - 1, matrixSide)] == CELL)
        result++;
    if (arr[correctXY(i, matrixSide)][correctXY(j + 1, matrixSide)] == CELL)
        result++;
    if (arr[correctXY(i + 1, matrixSide)][correctXY(j, matrixSide)] == CELL)
        result++;
    if (arr[correctXY(i - 1, matrixSide)][correctXY(j, matrixSide)] == CELL)
        result++;
    if (arr[correctXY(i + 1, matrixSide)][correctXY(j - 1, matrixSide)] == CELL)
        result++;
    if (arr[correctXY(i - 1, matrixSide)][correctXY(j - 1, matrixSide)] == CELL)
        result++;
    if (arr[correctXY(i - 1, matrixSide)][correctXY(j + 1, matrixSide)] == CELL)
        result++;
    if (arr[correctXY(i + 1, matrixSide)][correctXY(j + 1, matrixSide)] == CELL)
        result++;

    return result;
}

int correctXY(int coordinate, int matrixSide) {
    int correctCoordinate;

    if (coordinate < 0)
        correctCoordinate = matrixSide - 1;
    else if (coordinate > matrixSide - 1)
        correctCoordinate = 0;
    else
        correctCoordinate = coordinate;

    return correctCoordinate;
}

void getGenerationChange(char arr[][N], char tempArr[][N], int matrixSide) {
    for (int i = 0; i < matrixSide; i++) {
        for (int j = 0; j < matrixSide; j++) {
            livingCells = checkLivingCellsAround(tempArr, matrixSide, i, j);
            if (tempArr[i][j] == EMPTY && livingCells == 3)
                arr[i][j] = CELL;
            else if (livingCells == 0 && tempArr[i][j] == CELL)
                arr[i][j] = EMPTY;
            else if (livingCells == 1 && tempArr[i][j] == CELL)
                arr[i][j] = EMPTY;
            else if (livingCells >= 4 && tempArr[i][j] == CELL)
                arr[i][j] = EMPTY;
            else if (livingCells >= 2 && livingCells <= 3 && tempArr[i][j] == CELL)
                continue;
        }
    }
}

bool isCellsOnMatrix(char arr[][N], int matrixSide) {
    bool result = false;

    for (int i = 0; i < matrixSide; i++) {
        for (int j = 0; j < matrixSide; j++) {
            if (arr[i][j] == CELL) {
                result = true;
                break;
            }
        }
        if (result)
            break;
    }

    return result;
}

bool isGenerationChanged(char arr[][N], char tempArr[][N], int matrixSide) {
    bool result = false;

    for (int i = 0; i < matrixSide; i++) {
        for (int j = 0; j < matrixSide; j++) {
            if (arr[i][j] != tempArr[i][j]) {
                result = true;
                break;
            }
        }
        if (result)
            break;
    }

    return result;
}