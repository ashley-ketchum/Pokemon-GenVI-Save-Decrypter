/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Main)
    {
        if (Main->objectName().isEmpty())
            Main->setObjectName(QStringLiteral("Main"));
        Main->resize(400, 300);
        menuBar = new QMenuBar(Main);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Main->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Main);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Main->addToolBar(mainToolBar);
        centralWidget = new QWidget(Main);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Main->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Main);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Main->setStatusBar(statusBar);

        retranslateUi(Main);

        QMetaObject::connectSlotsByName(Main);
    } // setupUi

    void retranslateUi(QMainWindow *Main)
    {
        Main->setWindowTitle(QApplication::translate("Main", "Main", 0));
    } // retranslateUi

};

namespace Ui {
    class Main: public Ui_Main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
