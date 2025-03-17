#include "maingame.h"
#include "ui_maingame.h"
#include <QGridLayout>
#include <QDebug>

mainGame::mainGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainGame)
{
    ui->setupUi(this);
    sudoku = nullptr;
    innerBox = nullptr;
    //innerBox = nullptr;
    gridCreation();
}


int mainGame::getInnerSquare(int row, int col) {
    qDebug() <<"inside inner square, row is" << row;
    qDebug() << (row / 3) * 3 + (col / 3);
    return (row / 3) * 3 + (col / 3);
}
bool mainGame::isSafe(int row, int col, int num) {
    qDebug() << "Checking safety";
    //Checking row
    for (int j = 0; j < col; j++) {
        if (sudoku[row][j]->toPlainText().toInt() == num) {
            return false;
        }
    }

    //Checking column
    for (int i = 0; i < row; i++) {
        if (sudoku[i][col]->toPlainText().toInt() == num) {
            return false;
        }
    }
    //Checking inner square
    int innerSquareIndex = getInnerSquare(row, col);
    for (int i = 0; i < 9; i++ ) {
        if (innerBox[innerSquareIndex][i]->toPlainText().toInt() == num) {
            return false;
        }
    }
    return true;
}

void mainGame::gridCreation() {
    innerBox = new QTextEdit**[9];
    sudoku = new QTextEdit**[9];

    for (int i = 0; i < 9; i++) {
        innerBox[i] = new QTextEdit*[9];
        sudoku[i] = new QTextEdit*[9];

        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = new QTextEdit(this);
            sudoku[i][j]->setFixedSize(50, 50);

            // Initialize innerBox[i][j] to nullptr
            innerBox[i][j] = nullptr;
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // Calculate the inner square index and inner cell index
            int innerSquareIndex = getInnerSquare(i, j);
            int innerCellIndex = (i % 3) * 3 + (j % 3);

            // Assign the QTextEdit to the correct position in innerBox
            innerBox[innerSquareIndex][innerCellIndex] = sudoku[i][j];

            // Add the QTextEdit to the UI
            ui->SquareA->addWidget(sudoku[i][j], i, j);

            qDebug() << "Cell (" << i << "," << j << ") mapped to inner square" << innerSquareIndex << ", cell" << innerCellIndex;
        }
    }

    // Fill the grid with valid numbers
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j]->setText(QString::number(generator(i, j)));
        }
    }
}

int mainGame::generator(int row, int col) {
    int rando = rand() % 9 + 1;
    if (isSafe(row, col, rando)) {
        return rando;
    } else {
        generator(row, col);
    }
    return 0;
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
