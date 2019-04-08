#include "mainwindow.h"
#include "matdisplay.h"
#include "ui_mainwindow.h"

Ui::MainWindow* MainWindow::ui = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    MainWindow::ui = new Ui::MainWindow;
    MainWindow::ui->setupUi(this);

    connect(ui->Mat_DIsplay,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
    connect(ui->Mat_Display2,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition2(QPoint&)));
    connect(ui->File_open,SIGNAL(triggered()), this, SLOT(on_file_open_clicked()));
    connect(ui->File_save,SIGNAL(triggered()), this, SLOT(on_file_save_clicked()));
    connect(ui->Line_on,SIGNAL(triggered()),this, SLOT(on_line_on_clicked()));
    connect(ui->Line_off,SIGNAL(triggered()), this, SLOT(on_line_ofF_clicked()));
    connect(ui->Back_side,SIGNAL(triggered()), this, SLOT(on_back_side_clicked()));
    connect(ui->Right_side,SIGNAL(triggered()), this, SLOT(on_right_side_clicked()));
    connect(ui->Left_side,SIGNAL(triggered()), this, SLOT(on_left_side_clicked()));
    connect(ui->Upper_side,SIGNAL(triggered()), this, SLOT(on_upper_side_clicked()));
    connect(ui->img_seg,SIGNAL(triggered()),this,SLOT(on_img_segmentation_clicked()));

}

MainWindow::~MainWindow()
{
    delete MainWindow::ui;
}

void MainWindow::showMousePosition(QPoint &pos)
{
    ui->mouse_position_lable->setText("x: "+ QString::number(pos.x()) + ",y: "+ QString::number(pos.y()));
}

void MainWindow::showMousePosition2(QPoint& pos)
{
    ui->mouse_position_lable_2->setText("x: "+QString::number(pos.x()) + ",y: "+ QString::number(pos.y()));
}

void MainWindow::on_file_open_clicked()
{
    L_cnt = 0; //이미지를 새로 불러올 경우 카운트값을 0으로 초기화시킨다.
    line_flag = 0;
    QString filename = QFileDialog::getOpenFileName(this,
          tr("Open Image"), "../", tr("Image Files (*.png *.jpg *.bmp)"));

    cv::Mat img;
 
    /*
     *
     *  2017.08.01 QFiledialog 에서 한글 / 띄어쓰기가 포함된 경로가 제대로 안열릴 시
     * 생겼던 문제 해결, 기존에 filename.toStdString 을 아래와 같이 바꾸니 해결.
     * 참조 링크 : http://answers.opencv.org/question/43183/qt-imread-utf-8/
     * toLocal8Bit()함수만 사용하면 오류나오고 끝에 costData()를 붙여야 함.
     *
     */
    img = cv::imread(filename.toLocal8Bit().constData());

    if( !img.data ) {
        QMessageBox msg;
        msg.setText("No image, try again!");
        msg.exec();
    }

    cv::cvtColor(img,img,CV_BGR2RGB);
    ui->Mat_DIsplay->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
    ui->Mat_DIsplay->setScaledContents(true);
    cv::cvtColor(img,img,CV_RGB2BGR);
    cv::imwrite("current.jpg",img);
    image_w = img.rows;
    image_h = img.cols;
}

void MainWindow::on_file_save_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
          tr("Save Image"), "../", tr("Image Files (*.png *.jpg *.bmp)"));
}

void MainWindow::on_line_on_clicked()
{
    line_flag = 1;
    QMessageBox msg;
    msg.setText("excute line_on");
    msg.exec();
    ui->line_status->setText("current line status : ON");
}

void MainWindow::on_line_ofF_clicked()
{
    line_flag = 0;
    QMessageBox msg;
    msg.setText("excute line_off");
    msg.exec();
    ui->line_status->setText("current line status : OFF");
}

void MainWindow::on_back_side_clicked()
{
    location_mode = 1;
    QMessageBox msg;
    msg.setText("loaction : backside");
    msg.exec();
    ui->location_status->setText("Location status : backside");
    ui->line_order->setText("Click C7");
}

void MainWindow::on_right_side_clicked()
{
    location_mode = 2;
    QMessageBox msg;
    msg.setText("loaction : rightside");
    msg.exec();
    ui->location_status->setText(" Location status : rightside");
    ui->line_order->setText(" Click C7");
}

void MainWindow::on_left_side_clicked()
{
    location_mode = 3;
    QMessageBox msg;
    msg.setText("loaction : leftside");
    msg.exec();
    ui->location_status->setText(" Location status : leftside");
    ui->line_order->setText("Click C7");

}

void MainWindow::on_upper_side_clicked()
{
    location_mode = 4;
    QMessageBox msg;
    msg.setText("loaction : upperside");
    msg.exec();
    ui->location_status->setText(" Location status : upperside");
    ui->line_order->setText("Click right AC joint");
}

void MainWindow::on_img_segmentation_clicked()
{
    segmentation_mode = 1;
    ui->line_order->setText("image segmentation, value = "+QString::number(segmentation_mode));
}
