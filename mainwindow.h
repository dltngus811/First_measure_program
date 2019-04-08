#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "matdisplay.h"

#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QString>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    static Ui::MainWindow *ui;

public slots:

    void showMousePosition(QPoint& pos);
    void showMousePosition2(QPoint& pos);

private slots:
    void on_file_open_clicked();
    void on_file_save_clicked();
    void on_line_on_clicked();
    void on_line_ofF_clicked();
    void on_back_side_clicked();
    void on_right_side_clicked();
    void on_left_side_clicked();
    void on_upper_side_clicked();
    void on_img_segmentation_clicked();
};

#endif // MAINWINDOW_H

