
#ifndef MATDISPLAY_H
#define MATDISPLAY_H

#include "mainwindow.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QMouseEvent>
#include <QtCore/qmath.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

extern int R_cnt;
extern int L_cnt;
extern int arr_x;
extern int arr_y;
extern int value[12];

extern int image_w; // 불러온 이미지의 폭
extern int image_h; // 불러온 이미지의 너비
extern int ptx;     // 이미지와 label의 상대주소 (x좌표)
extern int pty;     // 이미지와 label의 상대주소 (y좌표)
extern int real_x;  // 실제 이미지에 찍힐 x좌표
extern int real_y;  // 실제 이미지에 찍힐 y좌표

extern float _t;
extern float _s;
extern float right_t;
extern float right_s;
extern float left_t;
extern float left_s;

extern float b[12];
extern int line_flag;           //cvline을 표현할건지 cvcircle을 표현할건지를 결정하는 flag변수
extern int location_mode;       //불러온 사진이 어떤 위치인지 구분하는 함수, 1=정면, 2=우측 측면, 3=좌측 측면, 4=윗면
extern int segmentation_mode;   //이미지를 분할하여 포개는 역할

class matDisplay : public QLabel
{
    Q_OBJECT


public:
    matDisplay(QWidget *parent = 0);
    ~matDisplay();


public:

    void mouseMoveEvent(QMouseEvent *mouse_event);
    void mousePressEvent(QMouseEvent *mouse_event);



signals:
    void sendMousePosition(QPoint&);


};

#endif // MATDISPLAY_H
