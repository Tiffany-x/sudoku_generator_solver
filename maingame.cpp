#include "maingame.h"
#include "ui_maingame.h"
#include <QGridLayout>
#include <QDebug>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <QIntValidator>
#include <QRegularExpressionValidator>

int sudokuArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

mainGame::mainGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainGame)
{
    srand (time(NULL));
    ui->setupUi(this);
    sudoku = nullptr;
    inside = nullptr;
    gridCreation();


    QWidget* buttonBG = new QWidget();
    //buttonBG->setStyleSheet("background-color: white;");
    buttonBG->setFixedHeight(550);
    buttonBG->setFixedWidth(300);

    QVBoxLayout* buttonLayout = new QVBoxLayout(buttonBG);
    ui->mainLayout->addWidget(buttonBG, 0, 1);
    ui->mainLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->setAlignment(Qt::AlignCenter);

    //Easy puzzle
    generateEasy = new QPushButton();
    connect(
        generateEasy, &QPushButton::clicked, [=]() {
        onEasy_clicked();
        }
    );
    generateEasy->setFixedHeight(40);
    generateEasy->setFixedWidth(200);
    generateEasy->setText("Generate Easy Puzzle");
    buttonLayout->addWidget(generateEasy);
    //easy end

    //Normal puzzle
    generateNormal = new QPushButton();
    connect(
        generateNormal, &QPushButton::clicked, [=]() {
            onNormal_clicked();
        }
        );
    generateNormal->setFixedHeight(40);
    generateNormal->setFixedWidth(200);
    generateNormal->setText("Generate Normal Puzzle");
    buttonLayout->addWidget(generateNormal);
    //Normal end

    //Hard puzzle
    generateHard = new QPushButton();
    connect(
        generateHard, &QPushButton::clicked, [=]() {
            onHard_clicked();
        }
        );
    generateHard->setFixedHeight(40);
    generateHard->setFixedWidth(200);
    generateHard->setText("Generate Hard Puzzle");
    buttonLayout->addWidget(generateHard);
    //Hard end

    //Extreme puzzle
    generateExtreme = new QPushButton();
    connect(
        generateExtreme, &QPushButton::clicked, [=]() {
            onExtreme_clicked();
        }
        );
    generateExtreme->setFixedHeight(40);
    generateExtreme->setFixedWidth(200);
    generateExtreme->setText("Generate Extreme Puzzle");
    buttonLayout->addWidget(generateExtreme);
    //Extreme end

    //regenerate
    regenerateGrid = new QPushButton();
    connect(
        regenerateGrid, &QPushButton::clicked, [=]() {
            onRegenerate_clicked();
        }
        );
    regenerateGrid->setFixedHeight(40);
    regenerateGrid->setFixedWidth(200);
    regenerateGrid->setText("Regenerate a grid");
    buttonLayout->addWidget(regenerateGrid);
    //regenerate end
}

//Easy slot
void mainGame::onEasy_clicked() {
    qDebug() << "Generate easy clicked";
    //deleteGrid();
    gridCreation();
    generatePuzzle("easy");
}

//Normal slot
void mainGame::onNormal_clicked() {
    qDebug() << "Generate normal clicked";
    //deleteGrid();
    gridCreation();
    generatePuzzle("normal");
}

//Hard slot
void mainGame::onHard_clicked() {
    qDebug() << "Generate hard clicked";
    //deleteGrid();
    gridCreation();
    generatePuzzle("hard");
}

//Extreme slot
void mainGame::onExtreme_clicked() {
    qDebug() << "Generate extreme clicked";
    //deleteGrid();
    gridCreation();
    generatePuzzle("extreme");
}

void mainGame::generatePuzzle(QString difficulty) {
    int blanks;

    if (QString::compare(difficulty, "easy", Qt::CaseInsensitive) == 0) {
        blanks = 5;
        qDebug() << "This is easy, there are " << blanks << " blanks.";
    } else if (QString::compare(difficulty, "normal", Qt::CaseInsensitive) == 0) {
        blanks = 6;
        qDebug() << "This is normal, there are " << blanks << " blanks.";
    } else if (QString::compare(difficulty, "hard", Qt::CaseInsensitive) == 0) {
        blanks = 7;
        qDebug() << "This is hard, there are " << blanks << " blanks.";
    } else {
        blanks = 8;
        qDebug() << "This is extreme, there are " << blanks << " blanks.";
    }


    for (int i = 0; i < 9; i++) {
        int blankArray[blanks];
        for (int j = 0; j < blanks; j++) {
            std::random_shuffle(&sudokuArray[0], &sudokuArray[9]);
            int random = (sudokuArray[1] - 1);
            for (int l = 0; l < blanks; l++) {
                if (blankArray[l] == random) {
                    random = (sudokuArray[l] - 1);
                    qDebug() << "Repeated random";
                }
            }
            blankArray[j] = random;
            qDebug() << "Blanks on row " << i << " should be in " << blankArray[j];
        }

        for (int k = 0; k < blanks; k++) {
            sudoku[i][blankArray[k]]->clear();
            gridValues[i][blankArray[k]] = 0;
        }

        for (int n = 0; n < 9; n++) {
            if (!sudoku[i][n]->text().isEmpty()) {

                sudoku[i][n]->setDisabled(true);
                sudoku[i][n]->setStyleSheet("background-color: LightBlue;");
            } else {
                sudoku[i][n]->setStyleSheet("background-color: white;");
            }
        }
    }
}

void mainGame::onRegenerate_clicked() {
    qDebug() << "Regenerate clicked";
    //deleteGrid();
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
    return (((row - minus_row) * 3) + (col - minus_col));
}

int mainGame::getInnerSquare(int row, int col) {
    return (row / 3) * 3 + (col / 3);
}

bool mainGame::isSafe(int row, int col, int num) {
    //Checking row
    for (int j = 0; j <9; j++) {
        if (gridValues[row][j] == num) {
            return false;
        }
    }

    //Checking column
    for (int i = 0; i < 9; i++) {
        if (gridValues[i][col] == num) {
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
    container = new QWidget();
    container->setStyleSheet("background-color: LemonChiffon;");
    container->setFixedWidth(380);
    container->setFixedHeight(380);

    SquareA = new QGridLayout(container);

    SquareA->setSpacing(5); // Remove default spacing
    SquareA->setContentsMargins(5, 5, 5, 5);

    memset(gridValues, 0, sizeof(gridValues));

    innerBox = new QLineEdit**[9];
    sudoku = new QLineEdit**[9];

    inside = new QGridLayout*[9];

    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            int index = m * 3 + n;
            QWidget* bg = new QWidget();
            bg->setStyleSheet("background-color: white;");
            bg->setFixedHeight(120);
            bg->setFixedWidth(120);
            inside[index] = new QGridLayout(bg);
            inside[index]->setSpacing(0); // Remove default spacing
            inside[index]->setContentsMargins(0,0,0,0);
            SquareA->addWidget(bg, m, n);
        }
    }


    for (int i = 0; i < 9; i++) {
        innerBox[i] = new QLineEdit*[9];
        sudoku[i] = new QLineEdit*[9];

        for (int j = 0; j < 9; j++) {

            sudoku[i][j] = new QLineEdit();
            sudoku[i][j]->setFixedSize(40, 40);
            sudoku[i][j]->setMaxLength(1);

            QRegularExpressionValidator *validator = new QRegularExpressionValidator(
QRegularExpression("^[1-9]$"),
                this);
            sudoku[i][j]->setValidator(validator);
            sudoku[i][j]->setAlignment(Qt::AlignCenter);
            connect(
                sudoku[i][j], &QLineEdit::textEdited, [=](const QString &value) {
                    onValue_entered(i, j, value.toInt());
                }
                );
            connect(
                sudoku[i][j], &QLineEdit::textChanged, [=](const QString &value) {
                    if (value.isEmpty()) {
                        sudoku[i][j]->setStyleSheet("background-color: white;");
                    }
                }
                );
        }
    }


    if (generator(0,0)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                int innerRow = i % 3;
                int innerCol = j % 3;

                inside[getInnerSquare(i, j)]->addWidget(sudoku[i][j], innerRow, innerCol);

                sudoku[i][j]->setText(QString::number(gridValues[i][j]));
                gridValues[i][j] = sudoku[i][j]->text().toInt();
                innerBox[getInnerSquare(i, j)][getInnerCellIndex(i, j)] = sudoku[i][j];

                }
        }
    }else {
        qDebug() << "Failed to generate Sudoku!";
    }
ui->mainLayout->addWidget(container, 0, 0);
}

void mainGame::onValue_entered(int row, int col, int value) {
    qDebug() << "Value entered is: " << value;

    if (!isSafe(row, col, value)) {
        qDebug() << "Not safe!";
        sudoku[row][col]->setStyleSheet("background-color: #FFC09F;");
    } else {
        sudoku[row][col]->setStyleSheet("background-color: white;");

    }
}
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
