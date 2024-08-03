#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_solveButton_clicked();
    void on_showRecursionButton_clicked();
    void on_speedDial_valueChanged(int value);
    void on_clearButton_clicked();
    void animateRecursion();
    void on_stopRecursionButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *recursionTimer; // This should be declared here
    std::vector<std::vector<char>> boardToSolve;
    std::vector<std::vector<std::vector<char>>> boardHistory;
    int currentRow;
    int currentCol;
    int speed;
    bool isAnimating;
    bool isSolving;

    bool isBoardValid(const std::vector<std::vector<char>> &board);
    bool isValid(std::vector<std::vector<char>> &board, int row, int col, char c);
    bool solveAndAnimate(std::vector<std::vector<char>>& board);
    std::vector<std::vector<char>> getBoardFromUI();
    void updateBoard(const std::vector<std::vector<char>> &board);
    bool solve(std::vector<std::vector<char>> &board);
};

#endif // MAINWINDOW_H
