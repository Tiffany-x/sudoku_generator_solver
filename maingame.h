#ifndef MAINGAME_H
#define MAINGAME_H

#include <QMainWindow>
#include <QTextEdit>


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




private:
    Ui::mainGame *ui;
    void gridCreation();
    void deleteGrid();
    bool generator(int row, int col);

    int gridValues[9][9];

    int getInnerCellIndex(int row, int col);
    bool isSafe(int row, int col, int num);

    int retry(int m, int n);
    int getInnerSquare(int row, int col);
 //   void inside(QTextEdit*** box);
//    QTextEdit*** innerBox;
    QTextEdit*** sudoku;
    QTextEdit*** innerBox;
};
#endif // MAINGAME_H
