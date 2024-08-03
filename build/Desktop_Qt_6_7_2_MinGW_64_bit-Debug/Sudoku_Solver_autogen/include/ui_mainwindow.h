/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *solveButton;
    QLabel *label;
    QTableWidget *sudokuTable;
    QPushButton *clearButton;
    QPushButton *showRecursionButton;
    QDial *speedDial;
    QLabel *label_2;
    QPushButton *stopRecursionButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(936, 676);
        MainWindow->setMinimumSize(QSize(450, 450));
        MainWindow->setMaximumSize(QSize(1000, 10000));
        MainWindow->setStyleSheet(QString::fromUtf8("gridline-color: rgb(85, 85, 255);"));
        MainWindow->setIconSize(QSize(40, 40));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(1000, 10000));
        solveButton = new QPushButton(centralwidget);
        solveButton->setObjectName("solveButton");
        solveButton->setGeometry(QRect(260, 560, 101, 31));
        solveButton->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\";\n"
"color: rgb(162, 167, 255);"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 30, 421, 31));
        label->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: rgb(162, 167, 255);"));
        sudokuTable = new QTableWidget(centralwidget);
        if (sudokuTable->columnCount() < 9)
            sudokuTable->setColumnCount(9);
        if (sudokuTable->rowCount() < 9)
            sudokuTable->setRowCount(9);
        sudokuTable->setObjectName("sudokuTable");
        sudokuTable->setGeometry(QRect(160, 80, 450, 450));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(sudokuTable->sizePolicy().hasHeightForWidth());
        sudokuTable->setSizePolicy(sizePolicy);
        sudokuTable->setMinimumSize(QSize(450, 450));
        sudokuTable->setMaximumSize(QSize(450, 450));
        sudokuTable->setStyleSheet(QString::fromUtf8("background-color: rgb(162, 167, 255);\n"
"font: 700 14pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        sudokuTable->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        sudokuTable->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        sudokuTable->setShowGrid(true);
        sudokuTable->setSortingEnabled(false);
        sudokuTable->setWordWrap(true);
        sudokuTable->setRowCount(9);
        sudokuTable->setColumnCount(9);
        sudokuTable->horizontalHeader()->setCascadingSectionResizes(false);
        sudokuTable->horizontalHeader()->setMinimumSectionSize(48);
        sudokuTable->horizontalHeader()->setDefaultSectionSize(62);
        sudokuTable->verticalHeader()->setCascadingSectionResizes(false);
        sudokuTable->verticalHeader()->setMinimumSectionSize(38);
        sudokuTable->verticalHeader()->setDefaultSectionSize(45);
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(410, 560, 101, 31));
        clearButton->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\";\n"
"color: rgb(162, 167, 255);"));
        showRecursionButton = new QPushButton(centralwidget);
        showRecursionButton->setObjectName("showRecursionButton");
        showRecursionButton->setGeometry(QRect(640, 180, 201, 61));
        showRecursionButton->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\";\n"
"color: rgb(162, 167, 255);"));
        speedDial = new QDial(centralwidget);
        speedDial->setObjectName("speedDial");
        speedDial->setGeometry(QRect(690, 270, 101, 71));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(690, 340, 141, 51));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(162, 167, 255);\n"
"font: 700 9pt \"Segoe UI\";"));
        stopRecursionButton = new QPushButton(centralwidget);
        stopRecursionButton->setObjectName("stopRecursionButton");
        stopRecursionButton->setGeometry(QRect(650, 400, 201, 61));
        stopRecursionButton->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\";\n"
"color: rgb(162, 167, 255);"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        solveButton->setText(QCoreApplication::translate("MainWindow", "Solve", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Soumili's Sudoku Solver :)", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        showRecursionButton->setText(QCoreApplication::translate("MainWindow", "Show Recursion", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Recursion speed ", nullptr));
        stopRecursionButton->setText(QCoreApplication::translate("MainWindow", "Stop Recursion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
