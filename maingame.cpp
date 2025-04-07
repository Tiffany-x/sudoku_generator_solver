#include "maingame.h"
#include "ui_maingame.h"
#include <QGridLayout>
#include <QDebug>
#include <time.h>
#include <stdlib.h>
#include <algorithm>


mainGame::mainGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainGame)
{
    srand (time(NULL));
    ui->setupUi(this);
    sudoku = nullptr;
    gridCreation();
}

int mainGame::getInnerCellIndex(int row, int col) {
    int minus_row;
    int minus_col;

    if (row < 3) {
        minus_row = 0;
    } else if (row >= 3 && row < 6) {
        minus_row = 3;
    } else {
        minus_row = 6;
    }

    if (col < 3) {
        minus_col = 0;
    } else if (col >= 3 && col < 6) {
        minus_col = 3;
    } else {
        minus_col = 6;
    }
    qDebug() << "inner cell is: " << ((row - minus_row) * 3) + (col - minus_col);
    return (((row - minus_row) * 3) + (col - minus_col));
}

int mainGame::getInnerSquare(int row, int col) {
    return (row / 3) * 3 + (col / 3);
}

bool mainGame::isSafe(int row, int col, int num) {
    //Checking row
    for (int j = 0; j <9; j++) {
        qDebug() << "Value in row is: " << gridValues[row][j];
        if (gridValues[row][j] == num) {
            qDebug() << "Unsafe in row";
            return false;
        }
    }

    //Checking column
    for (int i = 0; i < 9; i++) {
        qDebug() << "Value in col is: " << gridValues[i][col];
        if (gridValues[i][col] == num) {
            qDebug() << "Unsafe in column";
            return false;
        }
    }

    //Checking inner square
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gridValues[boxStartRow + i][boxStartCol + j] == num) {
                return false;
            }
        }
    }
    return true;
}

void mainGame::gridCreation() {

    memset(gridValues, 0, sizeof(gridValues));

    innerBox = new QTextEdit**[9];
    sudoku = new QTextEdit**[9];

    for (int i = 0; i < 9; i++) {
        innerBox[i] = new QTextEdit*[9];
        sudoku[i] = new QTextEdit*[9];

        for (int j = 0; j < 9; j++) {

            sudoku[i][j] = new QTextEdit(this);
            sudoku[i][j]->setFixedSize(50, 50);

            ui->SquareA->addWidget(sudoku[i][j], i, j);
        }
    }
    if (generator(0,0)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sudoku[i][j]->setText(QString::number(gridValues[i][j]));
                int innersquare = getInnerSquare(i, j);
                int innersquarecell = getInnerCellIndex(i, j);
                innerBox[innersquare][innersquarecell] = sudoku[i][j];
            }
        }
    }else {
        qDebug() << "Failed to generate Sudoku!";
    }

}

int sudokuArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

bool mainGame::generator(int row, int col) {
    if (row == 9) return true; // Successfully filled the grid
    if (col == 9) return generator(row + 1, 0); // Move to next row

    // Skip already filled cells
    if (gridValues[row][col] != 0) {
        return generator(row, col + 1);
    }

    std::random_shuffle(&sudokuArray[0], &sudokuArray[9]);
    for (int j = 0; j < 9; j++) {
        int num = sudokuArray[j];
        if (isSafe(row, col, num)) {
            gridValues[row][col] = num;
            if (generator(row, col + 1)) {
                return true;
            }
            gridValues[row][col] = 0; // Backtrack
        }
    }
    return false;
}

void mainGame::deleteGrid() {
    if (sudoku) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                delete sudoku[i][j];
            }
            delete[] sudoku[i];
        }
        delete[] sudoku;
        sudoku = nullptr;
    }

    if (innerBox) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                delete innerBox[i][j];
            }
            delete[] innerBox[i];
        }
        delete[] innerBox;
        innerBox = nullptr;
    }
}

mainGame::~mainGame()
{
    delete ui;
}
