#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFrame>
#include <QSet>
#include <set>
#include <QThread>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    recursionTimer(new QTimer(this)), // Initialize here
    currentRow(0),
    currentCol(0),
    speed(50), // Default speed
    isAnimating(false),
    isSolving(false)
{
    ui->setupUi(this);

    // Remove row and column headers
    ui->sudokuTable->horizontalHeader()->setVisible(false);
    ui->sudokuTable->verticalHeader()->setVisible(false);

    // Ensure the table is correctly sized
    ui->sudokuTable->setRowCount(9);
    ui->sudokuTable->setColumnCount(9);
    int tableSize = 450; // Adjust as needed
    ui->sudokuTable->setFixedSize(tableSize, tableSize);

    // Calculate and set the size for each cell
    int cellSize = tableSize / 9;
    for (int i = 0; i < 9; ++i) {
        ui->sudokuTable->setRowHeight(i, cellSize);
        ui->sudokuTable->setColumnWidth(i, cellSize);
    }

    // Create and add horizontal lines
    for (int row : {2, 5}) {
        QFrame* line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setGeometry(0, (row + 1) * cellSize - 1, tableSize, 2); // 2 pixels height
        line->setStyleSheet("background-color: black;"); // Color and thickness
        line->setParent(ui->sudokuTable); // Set parent to make sure it's drawn on the table
    }

    // Create and add vertical lines
    for (int col : {2, 5}) {
        QFrame* line = new QFrame(this);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setGeometry((col + 1) * cellSize - 1, 0, 2, tableSize); // 2 pixels width
        line->setStyleSheet("background-color: black;"); // Color and thickness
        line->setParent(ui->sudokuTable); // Set parent to make sure it's drawn on the table
    }

    // Populate the table
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ui->sudokuTable->setItem(i, j, new QTableWidgetItem());
            ui->sudokuTable->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked); // Connect clear button
    connect(ui->showRecursionButton, &QPushButton::clicked, this, &MainWindow::on_showRecursionButton_clicked);
    connect(ui->speedDial, &QDial::valueChanged, this, &MainWindow::on_speedDial_valueChanged);
    connect(ui->stopRecursionButton, &QPushButton::clicked, this, &MainWindow::on_stopRecursionButton_clicked);
    connect(recursionTimer, &QTimer::timeout, this, &MainWindow::animateRecursion);


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isBoardValid(const std::vector<std::vector<char>> &board)
{
    // Check rows
    for (int row = 0; row < 9; ++row) {
        std::set<char> seen;
        for (int col = 0; col < 9; ++col) {
            char num = board[row][col];
            if (num != '.' && !seen.insert(num).second) {
                return false; // Duplicate number in row
            }
        }
    }

    // Check columns
    for (int col = 0; col < 9; ++col) {
        std::set<char> seen;
        for (int row = 0; row < 9; ++row) {
            char num = board[row][col];
            if (num != '.' && !seen.insert(num).second) {
                return false; // Duplicate number in column
            }
        }
    }

    // Check 3x3 sub-grids
    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            std::set<char> seen;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    char num = board[startRow + i][startCol + j];
                    if (num != '.' && !seen.insert(num).second) {
                        return false; // Duplicate number in 3x3 sub-grid
                    }
                }
            }
        }
    }

    return true;
}

bool MainWindow::isValid(std::vector<std::vector<char>> &board, int row, int col, char c)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == c)
            return false;
        if (board[row][i] == c)
            return false;
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
            return false;
    }
    return true;
}

bool MainWindow::solveAndAnimate(std::vector<std::vector<char>>& board)
{
    if (!isSolving) return false; // Exit if solving has been stopped

    // Check if the board is fully solved
    bool solved = true;
    bool emptyCellFound = false;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == '.') {
                emptyCellFound = true;
                solved = false;
                for (char c = '1'; c <= '9'; ++c) {
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;
                        boardHistory.push_back(board); // Store current state
                        updateBoard(board);

                        QCoreApplication::processEvents(); // Ensure UI updates

                        QThread::msleep(speed); // Delay for animation effect

                        if (!isSolving) return false; // Stop recursion if isSolving is false

                        if (solveAndAnimate(board)) {
                            return true;
                        } else {
                            board[i][j] = '.'; // Reset on failure
                            boardHistory.push_back(board); // Store current state
                            updateBoard(board);

                            QCoreApplication::processEvents(); // Ensure UI updates

                            if (!isSolving) return false; // Stop recursion if isSolving is false

                            QThread::msleep(speed); // Delay for animation effect
                        }
                    }
                }
                return false; // If no number is valid, return false
            }
        }
    }

    // No empty cells found means the board is solved
    if (emptyCellFound) {
        boardHistory.push_back(board); // Store final solved state
        updateBoard(board);
        QCoreApplication::processEvents(); // Ensure UI updates

        if (!isSolving) return false; // Stop recursion if isSolving is false

        QThread::msleep(speed); // Delay for animation effect
    }
    return true;
}


void MainWindow::animateRecursion()
{
    if (!isAnimating) {
        // If we're not animating, do nothing
        return;
    }

    if (!isSolving) {
        // If solving is not active, stop animation and exit
        recursionTimer->stop();
        isAnimating = false;
        QMessageBox::information(this, "Sudoku Solver", "Animation stopped.");
        return;
    }

    // Show each state in history
    static size_t historyIndex = 0;
    if (historyIndex < boardHistory.size()) {
        updateBoard(boardHistory[historyIndex]);
        ++historyIndex;
    } else {
        recursionTimer->stop();
        isAnimating = false;
        historyIndex = 0; // Reset history index
    }
}

void MainWindow::on_speedDial_valueChanged(int value)
{
    speed = value;
    if (speed <= 0) speed = 1; // Prevent zero or negative speeds
    if (recursionTimer->isActive()) {
        recursionTimer->setInterval(1000 / speed);
    }
}

bool MainWindow::solve(std::vector<std::vector<char>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == '.')
            {
                for (char c = '1'; c <= '9'; c++)
                {
                    if (isValid(board, i, j, c))
                    {
                        board[i][j] = c;

                        if (solve(board) == true)
                            return true;
                        else
                            board[i][j] = '.';
                    }
                }
                return false; // for none of the numbers can be put in a cell
            }
        }
    }
    return true; // for all cells are filled
}

std::vector<std::vector<char>> MainWindow::getBoardFromUI()
{
    std::vector<std::vector<char>> board(9, std::vector<char>(9, '.'));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QString cellText = ui->sudokuTable->item(i, j)->text();
            if (!cellText.isEmpty() && cellText[0].isDigit()) {
                board[i][j] = cellText[0].toLatin1();
            }
        }
    }
    return board;
}

void MainWindow::updateBoard(const std::vector<std::vector<char>> &board)
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ui->sudokuTable->item(i, j)->setText(QString(board[i][j]));
        }
    }
}


void MainWindow::on_solveButton_clicked()
{
    std::vector<std::vector<char>> board = getBoardFromUI();

    // Validate the board before solving
    if (!isBoardValid(board)) {
        QMessageBox::warning(this, "Sudoku Solver", "The initial board configuration is invalid.");
        return;
    }

    if (solve(board)) {
        updateBoard(board);
    } else {
        QMessageBox::warning(this, "Sudoku Solver", "No solution exists for the given Sudoku.");
    }
}



void MainWindow::on_showRecursionButton_clicked()
{
    boardToSolve = getBoardFromUI(); // Get the current board state

    // Validate the board before solving
    if (!isBoardValid(boardToSolve)) {
        QMessageBox::warning(this, "Sudoku Solver", "The initial board configuration is invalid.");
        return;
    }

    boardHistory.clear(); // Clear previous history
    isAnimating = true;
    isSolving = true;

    // Set timer interval according to speed
    recursionTimer->setInterval(1000 / speed);

    // Start the timer
    recursionTimer->start();


    // Solve the board instantly
    if (solveAndAnimate(boardToSolve)) {
        updateBoard(boardToSolve);
    } else {
        QMessageBox::warning(this, "Sudoku Solver", "No solution exists for the given Sudoku.");
    }

}


void MainWindow::on_stopRecursionButton_clicked()
{
    if (isAnimating) {
        recursionTimer->stop();
        isAnimating = false;
        isSolving = false;
        //QMessageBox::information(this, "Sudoku Solver", "Recursion stopped.");
        // Create a QMessageBox
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Sudoku Solver");
        msgBox.setText("Recursion stopped.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);

        // Get the geometry of the main window
        QRect mainWindowRect = this->geometry();
        // Set the position of the message box to the right of the main window
        int xPos = mainWindowRect.x() + mainWindowRect.width() + 10; // 10 pixels to the right
        int yPos = mainWindowRect.y(); // Align with the top of the main window
        msgBox.move(xPos, yPos);

        // Show the message box
        msgBox.exec();

        // Reset history and board
        boardHistory.clear();
        //historyIndex = 0; // Ensure history index is reset
    }

}





void MainWindow::on_clearButton_clicked()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ui->sudokuTable->item(i, j)->setText(""); // Clear the text
        }
    }
}
