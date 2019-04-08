/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <matdisplay.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Line_on;
    QAction *Line_off;
    QAction *File_open;
    QAction *File_save;
    QAction *Back_side;
    QAction *Right_side;
    QAction *Left_side;
    QAction *Upper_side;
    QWidget *centralWidget;
    matDisplay *Mat_DIsplay;
    QLabel *mouse_position_lable;
    matDisplay *Mat_Display2;
    QLabel *mouse_position_lable_2;
    QTextBrowser *textBrowser_3;
    QLabel *mouse_position_lable_3;
    QTextBrowser *textBrowser_4;
    QLabel *mouse_position_lable_4;
    QTextBrowser *textBrowser_5;
    QLabel *mouse_position_lable_5;
    QTextBrowser *textBrowser_6;
    QLabel *mouse_position_lable_6;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QLabel *line_status;
    QLabel *line_order;
    QLabel *location_status;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu_Menu;
    QMenu *menuLine;
    QMenu *menuFile;
    QMenu *menuLocation;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 636);
        Line_on = new QAction(MainWindow);
        Line_on->setObjectName(QStringLiteral("Line_on"));
        Line_off = new QAction(MainWindow);
        Line_off->setObjectName(QStringLiteral("Line_off"));
        File_open = new QAction(MainWindow);
        File_open->setObjectName(QStringLiteral("File_open"));
        File_save = new QAction(MainWindow);
        File_save->setObjectName(QStringLiteral("File_save"));
        Back_side = new QAction(MainWindow);
        Back_side->setObjectName(QStringLiteral("Back_side"));
        Right_side = new QAction(MainWindow);
        Right_side->setObjectName(QStringLiteral("Right_side"));
        Left_side = new QAction(MainWindow);
        Left_side->setObjectName(QStringLiteral("Left_side"));
        Upper_side = new QAction(MainWindow);
        Upper_side->setObjectName(QStringLiteral("Upper_side"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Mat_DIsplay = new matDisplay(centralWidget);
        Mat_DIsplay->setObjectName(QStringLiteral("Mat_DIsplay"));
        Mat_DIsplay->setGeometry(QRect(10, 80, 512, 512));
        Mat_DIsplay->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        mouse_position_lable = new QLabel(centralWidget);
        mouse_position_lable->setObjectName(QStringLiteral("mouse_position_lable"));
        mouse_position_lable->setGeometry(QRect(1070, 40, 200, 50));
        mouse_position_lable->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        Mat_Display2 = new matDisplay(centralWidget);
        Mat_Display2->setObjectName(QStringLiteral("Mat_Display2"));
        Mat_Display2->setGeometry(QRect(540, 80, 512, 512));
        Mat_Display2->setStyleSheet(QLatin1String("background-color: rgb(212, 212, 212);\n"
""));
        mouse_position_lable_2 = new QLabel(centralWidget);
        mouse_position_lable_2->setObjectName(QStringLiteral("mouse_position_lable_2"));
        mouse_position_lable_2->setGeometry(QRect(1070, 130, 200, 50));
        mouse_position_lable_2->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        textBrowser_3 = new QTextBrowser(centralWidget);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(1070, 190, 200, 21));
        mouse_position_lable_3 = new QLabel(centralWidget);
        mouse_position_lable_3->setObjectName(QStringLiteral("mouse_position_lable_3"));
        mouse_position_lable_3->setGeometry(QRect(1070, 220, 200, 50));
        mouse_position_lable_3->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        textBrowser_4 = new QTextBrowser(centralWidget);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(1070, 280, 200, 21));
        mouse_position_lable_4 = new QLabel(centralWidget);
        mouse_position_lable_4->setObjectName(QStringLiteral("mouse_position_lable_4"));
        mouse_position_lable_4->setGeometry(QRect(1070, 310, 200, 50));
        mouse_position_lable_4->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        textBrowser_5 = new QTextBrowser(centralWidget);
        textBrowser_5->setObjectName(QStringLiteral("textBrowser_5"));
        textBrowser_5->setGeometry(QRect(1070, 370, 200, 21));
        mouse_position_lable_5 = new QLabel(centralWidget);
        mouse_position_lable_5->setObjectName(QStringLiteral("mouse_position_lable_5"));
        mouse_position_lable_5->setGeometry(QRect(1070, 400, 200, 50));
        mouse_position_lable_5->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        textBrowser_6 = new QTextBrowser(centralWidget);
        textBrowser_6->setObjectName(QStringLiteral("textBrowser_6"));
        textBrowser_6->setGeometry(QRect(1070, 460, 200, 21));
        mouse_position_lable_6 = new QLabel(centralWidget);
        mouse_position_lable_6->setObjectName(QStringLiteral("mouse_position_lable_6"));
        mouse_position_lable_6->setGeometry(QRect(1070, 490, 200, 90));
        mouse_position_lable_6->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(1070, 10, 200, 21));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(1070, 100, 200, 21));
        line_status = new QLabel(centralWidget);
        line_status->setObjectName(QStringLiteral("line_status"));
        line_status->setGeometry(QRect(10, 10, 151, 21));
        line_status->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        line_order = new QLabel(centralWidget);
        line_order->setObjectName(QStringLiteral("line_order"));
        line_order->setGeometry(QRect(10, 40, 511, 31));
        line_order->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        location_status = new QLabel(centralWidget);
        location_status->setObjectName(QStringLiteral("location_status"));
        location_status->setGeometry(QRect(170, 10, 161, 21));
        location_status->setStyleSheet(QStringLiteral("background-color: rgb(212, 212, 212);"));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 21));
        menu_Menu = new QMenu(menuBar);
        menu_Menu->setObjectName(QStringLiteral("menu_Menu"));
        menuLine = new QMenu(menu_Menu);
        menuLine->setObjectName(QStringLiteral("menuLine"));
        menuFile = new QMenu(menu_Menu);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuLocation = new QMenu(menu_Menu);
        menuLocation->setObjectName(QStringLiteral("menuLocation"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_Menu->menuAction());
        menu_Menu->addSeparator();
        menu_Menu->addAction(menuFile->menuAction());
        menu_Menu->addAction(menuLine->menuAction());
        menu_Menu->addAction(menuLocation->menuAction());
        menuLine->addAction(Line_on);
        menuLine->addAction(Line_off);
        menuFile->addSeparator();
        menuFile->addAction(File_open);
        menuFile->addAction(File_save);
        menuLocation->addAction(Back_side);
        menuLocation->addAction(Right_side);
        menuLocation->addAction(Left_side);
        menuLocation->addAction(Upper_side);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Line_on->setText(QApplication::translate("MainWindow", "Line_on", Q_NULLPTR));
        Line_off->setText(QApplication::translate("MainWindow", "Line_off", Q_NULLPTR));
        File_open->setText(QApplication::translate("MainWindow", "File_open", Q_NULLPTR));
        File_save->setText(QApplication::translate("MainWindow", "File_save", Q_NULLPTR));
        Back_side->setText(QApplication::translate("MainWindow", "Back_side", Q_NULLPTR));
        Right_side->setText(QApplication::translate("MainWindow", "Right_side", Q_NULLPTR));
        Left_side->setText(QApplication::translate("MainWindow", "Left_side", Q_NULLPTR));
        Upper_side->setText(QApplication::translate("MainWindow", "Upper_side", Q_NULLPTR));
        Mat_DIsplay->setText(QString());
        mouse_position_lable->setText(QString());
        Mat_Display2->setText(QString());
        mouse_position_lable_2->setText(QString());
        textBrowser_3->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\354\262\253 \353\262\210\354\247\270 \354\247\201\354\204\240 \354\242\214\355\221\234</p></body></html>", Q_NULLPTR));
        mouse_position_lable_3->setText(QString());
        textBrowser_4->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\353\221\220 \353\262\210\354\247\270 \354\247\201\354\204\240 \354\242\214\355\221\234</p></body></html>", Q_NULLPTR));
        mouse_position_lable_4->setText(QString());
        textBrowser_5->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\352\265\220\354\240\220\354\235\230 \354\242\214\355\221\234</p></body></html>", Q_NULLPTR));
        mouse_position_lable_5->setText(QString());
        textBrowser_6->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\352\260\201\353\217\204</p></body></html>", Q_NULLPTR));
        mouse_position_lable_6->setText(QString());
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\354\231\274\354\252\275 \354\235\264\353\257\270\354\247\200 \354\242\214\355\221\234</p></body></html>", Q_NULLPTR));
        textEdit_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\354\230\244\353\245\270\354\252\275 \354\235\264\353\257\270\354\247\200 \354\242\214\355\221\234</p></body></html>", Q_NULLPTR));
        line_status->setText(QString());
        line_order->setText(QString());
        location_status->setText(QString());
        menu_Menu->setTitle(QApplication::translate("MainWindow", "&Menu", Q_NULLPTR));
        menuLine->setTitle(QApplication::translate("MainWindow", "Line", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuLocation->setTitle(QApplication::translate("MainWindow", "Location", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
