#include "mainwindow.h"
#include "matdisplay.h"
#include "ui_mainwindow.h"

int L_cnt = 0;
int R_cnt = 0;
int arr_x = 0;
int arr_y = 0;
int abs_temp = 0;           //1번 포인트와 3번 포인트가 접점으로 잡힐지 정하는 변수
int abs_temp1 = 0;
int value[12] = {0};
int location_mode;              //불러온 사진이 어떤 위치인지 구분하는 함수, 1=정면, 2=우측 측면, 3=좌측 측면, 4=윗면
int segmentation_mode = 0;      //이미지를 분할하여 포개는 역할

int image_w = 0; // 불러온 이미지의 폭
int image_h = 0; // 불러온 이미지의 너비
int ptx = 0;     // 이미지와 label의 상대주소 (x좌표)
int pty = 0;     // 이미지와 label의 상대주소 (y좌표)
int real_x = 0;  // 실제 이미지에 찍힐 x좌표
int real_y = 0;  // 실제 이미지에 찍힐 y좌표

float dot;
float cross;
float alpha;

float right_ur_dot;
float right_ur_cross;
float right_ur_alpha;

float left_ur_dot;
float left_ur_cross;
float left_ur_alpha;

float right_st_dot;
float right_st_cross;
float right_st_alpha;

float left_st_dot;
float left_st_cross;
float left_st_alpha;

float right_pro_dot;
float right_pro_cross;
float right_pro_alpha;

float left_pro_dot;
float left_pro_cross;
float left_pro_alpha;

float right_ir_dot;
float right_ir_cross;
float right_ir_alpha;

float left_ir_dot;
float left_ir_cross;
float left_ir_alpha;

//직선의 방정식에 사용되는 포인터 변수
float right_t;
float right_s;
float left_t;
float left_s;

float right_st_t;
float right_st_s;
float left_st_t;
float left_st_s;

float _t;
float _s;
float b[12];

//cvline을 표현할건지 cvcircle을 표현할건지를 결정하는 flag변수
int line_flag = 0;

// 교점을 찾지 않아도 되는지에 대한 변수
int point_3 = 0;

cv::Point ab;
cv::Point cb;

cv::Point right_ab;
cv::Point right_cb;
cv::Point left_ab;
cv::Point left_cb;

cv::Point right_st_ab;
cv::Point right_st_cb;
cv::Point left_st_ab;
cv::Point left_st_cb;

cv::Point right_pro_ab;
cv::Point right_pro_cb;
cv::Point left_pro_ab;
cv::Point left_pro_cb;

cv::Point right_ir_ab;
cv::Point right_ir_cb;
cv::Point left_ir_ab;
cv::Point left_ir_cb;

matDisplay::matDisplay(QWidget* parent) :
    QLabel(parent)
{

    this->setMouseTracking(true);
}

matDisplay::~matDisplay()
{

}

void matDisplay::mouseMoveEvent(QMouseEvent *mouse_event)
{
    QPoint mouse_pos = mouse_event->pos();


    if(mouse_pos.x() <= this->size().width() && mouse_pos.y() <= this->size().height())
    {
        if(mouse_pos.x() >= 0 && mouse_pos.y() >= 0)
        {
            emit sendMousePosition(mouse_pos);
        }
    }

}

void matDisplay::mousePressEvent(QMouseEvent *mouse_event)
{
    QMessageBox msg;
    if(mouse_event->button() == Qt::LeftButton)
    {
        L_cnt++;
        msg.setText("Left Mouse Button Pressed!, cnt = "+QString::number(L_cnt));
        msg.exec();

        arr_x = mouse_event->pos().x();
        arr_y = mouse_event->pos().y();

        ptx = image_w / MainWindow::ui->Mat_DIsplay->width();
        pty = image_h / MainWindow::ui->Mat_DIsplay->height();

        cv::Mat img;

        // *1번 클릭 후에 segmentation mode일 경우
        if(segmentation_mode == 1)
        {
            cv::Mat image = cv::imread("current.jpg");

            QMessageBox msg;
            msg.setText("segmentation mode on");
            msg.exec();

            if( !image.data ) {
                QMessageBox msg;
                msg.setText("No image, try again!");
                msg.exec();
            }


            //cv::Rect rect(256,0,256,512);               //관심영역 설정 256,0 -> 시작지점, 256 = width, 512 = height
            //cv::Mat subImage = image(rect);             //관심영역 자르기
            //cv::flip(subImage,subImage,1);              //영상 반전, 0 = 상하, 1 = 좌우, -1 = 상하좌우
            //cv::cvtColor(subImage,subImage,CV_BGR2RGB); //영상 색상 rgb로 바꾸기, 안하면 파란색 이미지로 보임
            //MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(subImage.data,subImage.cols,subImage.rows,subImage.step,QImage::Format_RGB888)));


            cv::Mat image1 = cv::imread("current.jpg");
            cv::Mat result;
            cv::flip(image1,image1,1);
            cv::cvtColor(image,image,CV_BGR2RGB);
            //cv::cvtColor(image1,image1,CV_BGR2RGB);
            cv::addWeighted(image, 0.4, image1, 0.5, 0, result);
            MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(result.data,result.cols,result.rows,result.step,QImage::Format_RGB888)));
            MainWindow::ui->Mat_Display2->setScaledContents(true);

            segmentation_mode = 0;
        }

        // location : backside
        if(location_mode == 1)
        {
            if(L_cnt == 1)
            {
                MainWindow::ui->line_order->setText(" click T7");
                // value = 정수, b = 실수 || 좌표값 저장
                value[0] = mouse_event->pos().x();
                value[1] = mouse_event->pos().y();
                b[0] = mouse_event->pos().x() * ptx;
                b[1] = mouse_event->pos().y() * pty;

                img = cv::imread("current.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[0],b[1]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);

            }

            else if(L_cnt == 2)
            {
                MainWindow::ui->line_order->setText(" click Right RSS");
                // value = 정수, b = 실수 || 좌표값 저장
                value[2] = mouse_event->pos().x();
                value[3] = mouse_event->pos().y();
                b[2] = mouse_event->pos().x() * ptx;
                b[3] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(b[2],b[3]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                cv::line(img,cvPoint(b[0],b[1]),cvPoint(b[2],b[3]),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                MainWindow::ui->mouse_position_lable_3->setText("x: "+ QString::number(value[0]) + " , y : " + QString::number(value[1]) + "\nx: "+ QString::number(value[2]) + " , y : " + QString::number(value[3]));
            }

            else if(L_cnt == 3)
            {
                MainWindow::ui->line_order->setText(" click Right AC joint");
                // value = 정수, b = 실수 || 좌표값 저장
                value[4] = mouse_event->pos().x();
                value[5] = mouse_event->pos().y();
                b[4] = mouse_event->pos().x() * ptx;
                b[5] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[4],b[5]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
            }

            else if(L_cnt == 4)
            {
                MainWindow::ui->line_order->setText(" click Left RSS");
                // value = 정수, b = 실수 || 좌표값 저장
                value[6] = mouse_event->pos().x();
                value[7] = mouse_event->pos().y();
                b[6] = mouse_event->pos().x() * ptx;
                b[7] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(b[6],b[7]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                cv::line(img,cvPoint(b[4],b[5]),cvPoint(b[6],b[7]),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                MainWindow::ui->mouse_position_lable_4->setText("x: "+ QString::number(value[4]) + " , y : " + QString::number(value[5]) + "\nx: "+ QString::number(value[6]) + " , y : " + QString::number(value[7]));
            }

            else if(L_cnt == 5)
            {
                MainWindow::ui->line_order->setText(" click Left AC joint");
                // value = 정수, b = 실수 || 좌표값 저장
                value[8] = mouse_event->pos().x();
                value[9] = mouse_event->pos().y();
                b[8] = mouse_event->pos().x() * ptx;
                b[9] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[8],b[9]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
            }

            else if(L_cnt == 6)
            {
                MainWindow::ui->line_order->setText(" click C7");
                // value = 정수, b = 실수 || 좌표값 저장
                value[10] = mouse_event->pos().x();
                value[11] = mouse_event->pos().y();
                b[10] = mouse_event->pos().x() * ptx;
                b[11] = mouse_event->pos().y() * pty;

                /************교점 구하는 부분************/
                float right_ip_x;
                float right_ip_y;

                float left_ip_x;
                float left_ip_y;

                float right_under = ((b[5]-b[7])*(b[2]-b[0])) - ((b[4]-b[6])*(b[3]-b[1]));
                float left_under = ((b[9]-b[11])*(b[2]-b[0])) - ((b[8]-b[10])*(b[3]-b[1]));

                if(right_under==0 || left_under==0 ) {
                    MainWindow::ui->mouse_position_lable_5->setText("평행한 직선!");
                }

                float right__t = ((b[4]-b[6])*(b[1]-b[7])) - ((b[5]-b[7])*(b[0]-b[6]));
                float right__s = ((b[2]-b[0])*(b[1]-b[7])) - ((b[3]-b[1])*(b[0]-b[6]));

                float left__t = ((b[8]-b[10])*(b[1]-b[11])) - ((b[9]-b[11])*(b[0]-b[10]));
                float left__s = ((b[2]-b[0])*(b[1]-b[11])) - ((b[3]-b[1])*(b[0]-b[10]));

                right_t = right__t/right_under;
                right_s = right__s/right_under;

                left_t = left__t/left_under;
                left_s = left__s/left_under;


                if(right_t < 0.0 || right_t > 1.0 || right_s < 0.0 || right_s > 1.0 || left_t < 0.0 || left_t > 1.0 || left_s < 0.0 || left_s > 1.0) {
                    MainWindow::ui->mouse_position_lable_5->setText("s or t");
                }

                right_ip_x = b[0] + right_t * (float)(b[2]-b[0]);
                right_ip_y = b[1] + right_t * (float)(b[3]-b[1]);

                left_ip_x = b[0] + left_t * (float)(b[2]-b[0]) ;
                left_ip_y = b[1] + left_t * (float)(b[3]-b[1]) ;
                /************교점 구하는 부분 end************/

                /************좌표로 각도 구하는 부분************/
                // right ur angle, a=6,7 b=right_ip_x,right_ip_y c=2,3
                right_ab = { right_ip_x-b[6], right_ip_y-b[7] };
                right_cb = { right_ip_x-b[2], right_ip_y-b[3] };
                right_ur_dot = (right_ab.x * right_cb.x + right_ab.y * right_cb.y);
                right_ur_cross = (right_ab.x * right_cb.y - right_ab.y * right_cb.x);
                right_ur_alpha = atan2(right_ur_cross, right_ur_dot);
                right_ur_alpha = right_ur_alpha*(180/3.14159265);

                // left ur angle, a=2,3 b=left_ip_x,left_ip_y c=10,11
                left_ab = { left_ip_x - b[2], left_ip_y-b[3] };
                left_cb = { left_ip_x - b[10], left_ip_y-b[11] };
                left_ur_dot = (left_ab.x * left_cb.x + left_ab.y * left_cb.y);
                left_ur_cross = (left_ab.x * left_cb.y - left_ab.y * left_cb.x);
                left_ur_alpha = atan2(left_ur_cross, left_ur_dot);
                left_ur_alpha = left_ur_alpha*(180/3.14159265);

                // right st angle, a=6,7 b=0,1 c=2,3
                right_st_ab = { b[0]-b[6], b[1]-b[7] };
                right_st_cb = { b[0]-b[2], b[1]-b[3] };
                right_st_dot = ( right_st_ab.x * right_st_cb.x + right_st_ab.y * right_st_cb.y );
                right_st_cross = ( right_st_ab.x * right_st_cb.y + right_st_ab.y * right_st_cb.x );
                right_st_alpha = atan2(right_st_cross, right_st_dot);
                right_st_alpha = right_st_alpha*(180/3.14159265);

                // left st angle, a=2,3 b=0,1 c=10,11
                left_st_ab = { b[0]-b[2], b[1]-b[3] };
                left_st_cb = { b[0]-b[10], b[1]-b[11] };
                left_st_dot = ( left_st_ab.x * left_st_cb.x + left_st_ab.y * left_st_cb.y );
                left_st_cross = ( left_st_ab.x * left_st_cb.y - left_st_ab.y * left_st_cb.x );
                left_st_alpha = atan2(left_st_cross, left_st_dot);
                left_st_alpha = left_st_alpha*(180/3.14159265);
                MainWindow::ui->mouse_position_lable_6->setText("Lt ST angle : "+ QString::number(left_st_alpha)+
                                                                "\n"+"Rt ST angle : "+ QString::number(right_st_alpha)+
                                                                "\nLt UR angle : "+ QString::number(left_ur_alpha)+
                                                                "\n"+"Rt UR angle : "+ QString::number(right_ur_alpha));
                /************좌표로 각도 구하는 부분 end ************/
                MainWindow::ui->mouse_position_lable_4->setText("x: "+ QString::number(value[4]) + " , y : " + QString::number(value[5]) + "\nx: "+ QString::number(value[6]) + " , y : " + QString::number(value[7]));
                MainWindow::ui->mouse_position_lable_5->setText("Lt inter x : " +QString::number((int)left_ip_x)+"\tRt inter x : " +QString::number((int)right_ip_x)+
                                                                "\nLt inter y : " +QString::number((int)left_ip_y)+ "\tRt inter y : " +QString::number((int)right_ip_y));

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(int(right_ip_x),int(right_ip_y)),5,CV_RGB(0,255,0),2,8,0);
                cv::circle(img,cvPoint(int(left_ip_x),int(left_ip_y)),5,CV_RGB(0,255,0),2,8,0);
                cv::circle(img,cvPoint(b[10],b[11]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                    cv::line(img,cvPoint(b[0],b[1]),cvPoint(b[2],b[3]),CV_RGB(0,0,255),2);
                    cv::line(img,cvPoint(b[4],b[5]),cvPoint(b[6],b[7]),CV_RGB(0,0,255),2);
                    cv::line(img,cvPoint(b[8],b[9]),cvPoint(b[10],b[11]),CV_RGB(0,0,255),2);
                    cv::line(img,cvPoint(b[4],b[5]),cvPoint(right_ip_x,right_ip_y),CV_RGB(0,255,0),2);
                    cv::line(img,cvPoint(b[8],b[9]),cvPoint(left_ip_x,left_ip_y),CV_RGB(0,255,0),2);
                    cv::line(img,cvPoint(b[6],b[7]),cvPoint(b[0],b[1]),CV_RGB(0,255,0),2);
                    cv::line(img,cvPoint(b[10],b[11]),cvPoint(b[0],b[1]),CV_RGB(0,255,0),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                L_cnt = 0;
            }
        }

        // location : rightside
        else if(location_mode == 2)
        {
            if(L_cnt == 1)
            {
                MainWindow::ui->line_order->setText(" click T7");
                // value = 정수, b = 실수 || 좌표값 저장
                value[0] = mouse_event->pos().x();
                value[1] = mouse_event->pos().y();
                b[0] = mouse_event->pos().x() * ptx;
                b[1] = mouse_event->pos().y() * pty;

                img = cv::imread("current.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[0],b[1]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);

            }

            else if(L_cnt == 2)
            {
                MainWindow::ui->line_order->setText(" click scapula medial border(upper)");
                // value = 정수, b = 실수 || 좌표값 저장
                value[2] = mouse_event->pos().x();
                value[3] = mouse_event->pos().y();
                b[2] = mouse_event->pos().x() * ptx;
                b[3] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(b[2],b[3]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                cv::line(img,cvPoint(b[0],b[1]),cvPoint(b[2],b[3]),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                MainWindow::ui->mouse_position_lable_3->setText("x: "+ QString::number(value[0]) + " , y : " + QString::number(value[1]) + "\nx: "+ QString::number(value[2]) + " , y : " + QString::number(value[3]));
            }

            else if(L_cnt == 3)
            {
                MainWindow::ui->line_order->setText(" click scapula medial border(lower)");
                // value = 정수, b = 실수 || 좌표값 저장
                value[4] = mouse_event->pos().x();
                value[5] = mouse_event->pos().y();
                b[4] = mouse_event->pos().x() * ptx;
                b[5] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[4],b[5]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
            }

            else if(L_cnt == 4)
            {

                MainWindow::ui->line_order->setText(" click C7");
                // value = 정수, b = 실수 || 좌표값 저장
                value[6] = mouse_event->pos().x();
                value[7] = mouse_event->pos().y();
                b[6] = mouse_event->pos().x() * ptx;
                b[7] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(b[6],b[7]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                cv::line(img,cvPoint(b[4],b[5]),cvPoint(b[6],b[7]),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                MainWindow::ui->mouse_position_lable_4->setText("x: "+ QString::number(value[4]) + " , y : " + QString::number(value[5]) + "\nx: "+ QString::number(value[6]) + " , y : " + QString::number(value[7]));

                /************교점 구하는 부분************/
                float t;
                float s;
                float under = (b[7]-b[5])*(b[2]-b[0])-(b[6]-b[4])*(b[3]-b[1]);
                float ip_x;
                float ip_y;

                if(under==0)
                {
                    MainWindow::ui->mouse_position_lable_5->setText("평행한 직선!");
                }

                _t = (b[6]-b[4])*(b[1]-b[5]) - (b[7]-b[5])*(b[0]-b[4]);
                _s = (b[2]-b[0])*(b[1]-b[5]) - (b[3]-b[1])*(b[0]-b[4]);

                t = _t/under;
                s = _s/under;

                if(t<0.0 || t>1.0 || s<0.0 || s>1.0)
                {
                    MainWindow::ui->mouse_position_lable_5->setText("s or t");
                }

                ip_x = b[0] + t * (float)(b[2]-b[0]);
                ip_y = b[1] + t * (float)(b[3]-b[1]);
                MainWindow::ui->mouse_position_lable_5->setText("교점의 좌표\nx : " +QString::number((int)ip_x)+ " y : " +QString::number((int)ip_y));
                /************교점 구하는 부분 end************/


                /************좌표로 각도 구하는 부분************/
                ab = { ip_x - b[2], ip_y - b[3] }; //ab벡터
                cb = { ip_x - b[6], ip_y - b[7] }; //cb벡터
                dot = (ab.x * cb.x + ab.y * cb.y); // dot product = a놈 * b놈 * cosA //밑변
                cross = (ab.x * cb.y - ab.y * cb.x); // cross product = a놈 * b놈 * sinA //높이
                alpha = atan2(cross, dot); // tan = sin/cos
                alpha = alpha*(180/3.14159265);
                MainWindow::ui->mouse_position_lable_6->setText("AT angle : "+ QString::number(alpha));
                /************좌표로 각도 구하는 부분 end ************/

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(int(ip_x),int(ip_y)),5,CV_RGB(0,255,0),2,8,0);
                //cv::circle(img,cvPoint(arr_x,arr_y),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                    cv::line(img,cvPoint(b[4],b[5]),cvPoint(b[6],b[7]),CV_RGB(0,0,255),2);
                    cv::line(img,cvPoint(b[4],b[5]),cvPoint((int)(ip_x),(int)(ip_y)),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                L_cnt = 0;
            }
        }

        // location : leftside
        else if(location_mode == 3)
        {
            if(L_cnt == 1)
            {
                MainWindow::ui->line_order->setText(" click T7");
                // value = 정수, b = 실수 || 좌표값 저장
                value[0] = mouse_event->pos().x();
                value[1] = mouse_event->pos().y();
                b[0] = mouse_event->pos().x() * ptx;
                b[1] = mouse_event->pos().y() * pty;

                img = cv::imread("current.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[0],b[1]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);

            }

            else if(L_cnt == 2)
            {
                MainWindow::ui->line_order->setText(" click scapula medial border(upper)");
                // value = 정수, b = 실수 || 좌표값 저장
                value[2] = mouse_event->pos().x();
                value[3] = mouse_event->pos().y();
                b[2] = mouse_event->pos().x() * ptx;
                b[3] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(b[2],b[3]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                cv::line(img,cvPoint(b[0],b[1]),cvPoint(b[2],b[3]),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                MainWindow::ui->mouse_position_lable_3->setText("x: "+ QString::number(value[0]) + " , y : " + QString::number(value[1]) + "\nx: "+ QString::number(value[2]) + " , y : " + QString::number(value[3]));
            }

            else if(L_cnt == 3)
            {
                MainWindow::ui->line_order->setText(" click scapula medial border(lower)");
                // value = 정수, b = 실수 || 좌표값 저장
                value[4] = mouse_event->pos().x();
                value[5] = mouse_event->pos().y();
                b[4] = mouse_event->pos().x() * ptx;
                b[5] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[4],b[5]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
            }

            else if(L_cnt == 4)
            {

                MainWindow::ui->line_order->setText(" click C7");
                // value = 정수, b = 실수 || 좌표값 저장
                value[6] = mouse_event->pos().x();
                value[7] = mouse_event->pos().y();
                b[6] = mouse_event->pos().x() * ptx;
                b[7] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(b[6],b[7]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                cv::line(img,cvPoint(b[4],b[5]),cvPoint(b[6],b[7]),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                MainWindow::ui->mouse_position_lable_4->setText("x: "+ QString::number(value[4]) + " , y : " + QString::number(value[5]) + "\nx: "+ QString::number(value[6]) + " , y : " + QString::number(value[7]));

                /************교점 구하는 부분************/
                float t;
                float s;
                float under = (b[7]-b[5])*(b[2]-b[0])-(b[6]-b[4])*(b[3]-b[1]);
                float ip_x;
                float ip_y;

                if(under==0)
                {
                    MainWindow::ui->mouse_position_lable_5->setText("평행한 직선!");
                }

                _t = (b[6]-b[4])*(b[1]-b[5]) - (b[7]-b[5])*(b[0]-b[4]);
                _s = (b[2]-b[0])*(b[1]-b[5]) - (b[3]-b[1])*(b[0]-b[4]);

                t = _t/under;
                s = _s/under;

                if(t<0.0 || t>1.0 || s<0.0 || s>1.0)
                {
                    MainWindow::ui->mouse_position_lable_5->setText("s or t");
                }

                ip_x = b[0] + t * (float)(b[2]-b[0]);
                ip_y = b[1] + t * (float)(b[3]-b[1]);
                MainWindow::ui->mouse_position_lable_5->setText("교점의 좌표\nx : " +QString::number((int)ip_x)+ " y : " +QString::number((int)ip_y));
                /************교점 구하는 부분 end************/

                /************좌표로 각도 구하는 부분************/
                // AT angle, a=6,7 b=ip_x,ip_y c=2,3
                ab = { ip_x - b[6], ip_y - b[7] }; //ab벡터
                cb = { ip_x - b[2], ip_y - b[3] }; //cb벡터
                dot = (ab.x * cb.x + ab.y * cb.y); // dot product = a놈 * b놈 * cosA //밑변
                cross = (ab.x * cb.y - ab.y * cb.x); // cross product = a놈 * b놈 * sinA //높이
                alpha = atan2(cross, dot); // tan = sin/cos
                alpha = alpha*(180/3.14159265);
                MainWindow::ui->mouse_position_lable_6->setText("AT angle : "+ QString::number(alpha));
                /************좌표로 각도 구하는 부분 end ************/

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(int(ip_x),int(ip_y)),5,CV_RGB(0,255,0),2,8,0);
                //cv::circle(img,cvPoint(arr_x,arr_y),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                    cv::line(img,cvPoint(b[4],b[5]),cvPoint(b[6],b[7]),CV_RGB(0,0,255),2);
                    cv::line(img,cvPoint(b[4],b[5]),cvPoint((int)(ip_x),(int)(ip_y)),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                L_cnt = 0;
            }
        }

        // location : upperside
        else if(location_mode == 4)
        {
            if(L_cnt == 1)
            {
                MainWindow::ui->line_order->setText(" click Left AC joint");
                // value = 정수, b = 실수 || 좌표값 저장
                value[0] = mouse_event->pos().x();
                value[1] = mouse_event->pos().y();
                b[0] = mouse_event->pos().x() * ptx;
                b[1] = mouse_event->pos().y() * pty;

                img = cv::imread("current.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[0],b[1]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);

            }

            else if(L_cnt == 2)
            {
                MainWindow::ui->line_order->setText(" click Center of C7 vertebral body");
                // value = 정수, b = 실수 || 좌표값 저장
                value[2] = mouse_event->pos().x();
                value[3] = mouse_event->pos().y();
                b[2] = mouse_event->pos().x() * ptx;
                b[3] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(b[2],b[3]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                //cv::line(img,cvPoint(b[0],b[1]),cvPoint(b[2],b[3]),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                MainWindow::ui->mouse_position_lable_3->setText("x: "+ QString::number(value[0]) + " , y : " + QString::number(value[1]) + "\nx: "+ QString::number(value[2]) + " , y : " + QString::number(value[3]));
            }

            else if(L_cnt == 3)
            {
                MainWindow::ui->line_order->setText(" click Parallel to C7-T7 vertebral axis");
                // value = 정수, b = 실수 || 좌표값 저장
                value[4] = mouse_event->pos().x();
                value[5] = mouse_event->pos().y();
                b[4] = mouse_event->pos().x() * ptx;
                b[5] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[4],b[5]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
            }

            else if(L_cnt == 4)
            {
                MainWindow::ui->line_order->setText(" click Right RSS");
                // value = 정수, b = 실수 || 좌표값 저장
                value[6] = mouse_event->pos().x();
                value[7] = mouse_event->pos().y();
                b[6] = mouse_event->pos().x() * ptx;
                b[7] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);   // Q. 왜 주석처리해야 정상적인 컬러이미지가 뜨는건지?
                cv::circle(img,cvPoint(b[6],b[7]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                //cv::line(img,cvPoint(b[4],b[5]),cvPoint(b[6],b[7]),CV_RGB(0,0,255),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                MainWindow::ui->mouse_position_lable_4->setText("x: "+ QString::number(value[4]) + " , y : " + QString::number(value[5]) + "\nx: "+ QString::number(value[6]) + " , y : " + QString::number(value[7]));
            }

            else if(L_cnt == 5)
            {
                MainWindow::ui->line_order->setText(" click Left RSS");
                // value = 정수, b = 실수 || 좌표값 저장
                value[8] = mouse_event->pos().x();
                value[9] = mouse_event->pos().y();
                b[8] = mouse_event->pos().x() * ptx;
                b[9] = mouse_event->pos().y() * pty;

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                cv::circle(img,cvPoint(b[8],b[9]),5,CV_RGB(0,0,255),2,8,0);
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
            }

            else if(L_cnt == 6)
            {
                MainWindow::ui->line_order->setText(" Right AC joint");
                // value = 정수, b = 실수 || 좌표값 저장
                value[10] = mouse_event->pos().x();
                value[11] = mouse_event->pos().y();
                b[10] = mouse_event->pos().x() * ptx;
                b[11] = mouse_event->pos().y() * pty;


                // right PRO angle, a=0,1 b=4,5 c=6,7
                right_pro_ab = { b[4]-b[0], b[5]-b[1] };
                right_pro_cb = { b[4]-b[6], b[4]-b[7] };
                right_pro_dot = ( right_pro_ab.x * right_pro_cb.x + right_pro_ab.y * right_pro_cb.y );
                right_pro_cross = ( right_pro_ab.x * right_pro_cb.y - right_pro_ab.y * right_pro_cb.x );
                right_pro_alpha = atan2(right_pro_cross, right_pro_dot);
                right_pro_alpha = right_pro_alpha*(180/3.14159265);

                // left PRO angle, a=6,7 b=4,5 c=2,3
                left_pro_ab = { b[4]-b[6], b[5]-b[7] };
                left_pro_cb = { b[4]-b[2], b[5]-b[3] };
                left_pro_dot = ( left_pro_ab.x * left_pro_cb.x + left_pro_ab.y * left_pro_cb.y );
                left_pro_cross = ( left_pro_ab.x * left_pro_cb.y - left_pro_ab.y * left_pro_cb.x );
                left_pro_alpha = atan2(left_pro_cross, left_pro_dot);
                left_pro_alpha = left_pro_alpha*(180/3.14159265);

                // right IR angle, a=8,9 b=0,1 c=2,3
                right_ir_ab = { b[0]-b[8], b[1]-b[9] };
                right_ir_cb = { b[0]-b[2], b[1]-b[3] };
                right_ir_dot = ( right_ir_ab.x * right_ir_cb.x + right_ir_ab.y * right_ir_cb.y );
                right_ir_cross = ( right_ir_ab.x * right_ir_cb.y - right_ir_ab.y * right_ir_cb.x );
                right_ir_alpha = atan2(right_ir_cross, right_ir_dot);
                right_ir_alpha = right_ir_alpha*(180/3.14159265);

                // left IR angle, a=0,1 b=2,3 c=10,11
                left_ir_ab = { b[2]-b[0], b[3]-b[1] };
                left_ir_cb = { b[2]-b[10], b[3]-b[11] };
                left_ir_dot = ( left_ir_ab.x * left_ir_cb.x + left_ir_ab.y * left_ir_cb.y );
                left_ir_cross = ( left_ir_ab.x * left_ir_cb.y - left_ir_ab.y * left_ir_cb.x );
                left_ir_alpha = atan2(left_ir_cross, left_ir_dot);
                left_ir_alpha = left_ir_alpha*(180/3.14159265);

                MainWindow::ui->mouse_position_lable_6->setText("Rt PRO angle : "+ QString::number(right_pro_alpha)+
                                                                "\nLt PRO angle : "+ QString::number(left_pro_alpha)+
                                                                "\nRt IR angle : "+ QString::number(right_ir_alpha)+
                                                                "\nLt IR angle : "+ QString::number(left_ir_alpha));

                /************좌표로 각도 구하는 부분 end ************/
                MainWindow::ui->mouse_position_lable_4->setText("x: "+ QString::number(value[4]) + " , y : " + QString::number(value[5]) + "\nx: "+ QString::number(value[6]) + " , y : " + QString::number(value[7]));
                //MainWindow::ui->mouse_position_lable_5->setText("오른쪽 교점 x : " +QString::number((int)right_ip_x)+ " y : " +QString::number((int)right_ip_y)+
                //                                                "\n  왼쪽  교점 x : " +QString::number((int)left_ip_x)+ " y : " +QString::number((int)left_ip_y));

                img = cv::imread("current1.jpg");
                cv::cvtColor(img,img,CV_BGR2RGB);
                //cv::circle(img,cvPoint(int(right_ip_x),int(right_ip_y)),5,CV_RGB(0,255,0),2,8,0);
                //cv::circle(img,cvPoint(int(left_ip_x),int(left_ip_y)),5,CV_RGB(0,255,0),2,8,0);
                cv::circle(img,cvPoint(b[10],b[11]),5,CV_RGB(0,0,255),2,8,0);
                if(line_flag == 1)
                {
                    cv::line(img,cvPoint(b[0],b[1]),cvPoint(b[4],b[5]),CV_RGB(0,0,255),2);
                    cv::line(img,cvPoint(b[2],b[3]),cvPoint(b[4],b[5]),CV_RGB(0,0,255),2);
                    cv::line(img,cvPoint(b[4],b[5]),cvPoint(b[6],b[7]),CV_RGB(0,0,255),2);
                    cv::line(img,cvPoint(b[8],b[9]),cvPoint(b[0],b[1]),CV_RGB(0,255,0),2);
                    cv::line(img,cvPoint(b[0],b[1]),cvPoint(b[2],b[3]),CV_RGB(0,255,0),2);
                    cv::line(img,cvPoint(b[2],b[3]),cvPoint(b[10],b[11]),CV_RGB(0,255,0),2);
                }
                MainWindow::ui->Mat_Display2->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
                MainWindow::ui->Mat_Display2->setScaledContents(true);
                cv::cvtColor(img,img,CV_RGB2BGR);
                cv::imwrite("current1.jpg",img);
                L_cnt = 0;
            }
        }

    }




    else if(mouse_event->button() == Qt::RightButton)
    {
        R_cnt++;
        msg.setText("Right Mouse Button Pressed!, cnt = "+QString::number(R_cnt));
        msg.exec();

        if(R_cnt == 8)
        {
            R_cnt = 0;
        }
    }

}


