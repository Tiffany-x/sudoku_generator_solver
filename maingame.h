#ifndef MAINGAME_H
#define MAINGAME_H

#include <QMainWindow>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui {
class mainGame;
}
QT_END_NAMESPACE

class mainGame : public QMainWindow
{
    Q_OBJECT

public:
    mainGame(QWidget *parent = nullptr);
    ~mainGame();

private slots:
    void onRegenerate_clicked();
    void onEasy_clicked();
    void onNormal_clicked();
    void onHard_clicked();
    void onExtreme_clicked();

    void onValue_entered(int row, int col, int value);


private:
    Ui::mainGame *ui;
    void gridCreation();
    void deleteGrid();
    void generatePuzzle(QString difficulty);


    bool generator(int row, int col);

    int gridValues[9][9];

    int getInnerCellIndex(int row, int col);
    bool isSafe(int row, int col, int num);

    int retry(int m, int n);
    int getInnerSquare(int row, int col);
 //   void inside(QLineEdit*** box);
//    QLineEdit*** innerBox;

    QGridLayout* SquareA;
    QLineEdit*** sudoku;
    QLineEdit*** innerBox;
    QGridLayout** inside;
    QWidget* container;

    QPushButton* generateEasy;
    QPushButton* generateNormal;
    QPushButton* generateHard;
    QPushButton* generateExtreme;

    QPushButton* regenerateGrid;
};
#endif // MAINGAME_H
