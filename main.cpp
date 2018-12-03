#include <opencv2/opencv.hpp>
#include <iostream>
#include <enery.h>
#define DELAY_TIME 1
#define PI 3.14
using namespace cv;
using namespace std;

Point2f EneryCenter = Point2f(320,240);
int main(int argc,char** argv)
{
    Mat src = Mat::zeros(480,640,CV_32FC3);
    namedWindow("src", CV_WINDOW_AUTOSIZE);

    EneryAT::MoveArmor Ar[5];
    EneryAT::EneryStick EAstick[5];

    /**************init angry******/
    for(int i=0;i<5;i++)
    {
        //draw enery stick
        EAstick[i].angry = PI/2 + i*2*PI/5;

        float x1 = EAstick[i].rou1*cos(EAstick[i].angry);
        float y1 = EAstick[i].rou1*sin(EAstick[i].angry);
        x1 = x1 + EneryCenter.x;
        y1 = -y1 + EneryCenter.y;
        EAstick[i].pot1 = Point2f(x1,y1);
        float x2 = EAstick[i].rou2*cos(EAstick[i].angry);
        float y2 = EAstick[i].rou2*sin(EAstick[i].angry);
        x2 = x2 + EneryCenter.x;
        y2 = -y2 + EneryCenter.y;
        EAstick[i].pot2 = Point2f(x2,y2);
        EAstick[i].DrawEneryStick(src);
        //draw move armor
        Ar[i].angry = EAstick[i].angry + PI/2;
//        while(Ar[i].angry>=PI)
//            Ar[i].angry -= PI;
        Ar[i].pot.clear();
//        Point2f p1 = Point2f(-Ar[i].width*cos(Ar[i].angry)+EAstick[i].pot1.x,
//                             Ar[i].width*sin(Ar[i].angry)+EAstick[i].pot1.y);
//        Point2f p2 = Point2f(Ar[i].width*cos(Ar[i].angry)+EAstick[i].pot1.x,
//                             -Ar[i].width*sin(Ar[i].angry)+EAstick[i].pot1.y);
//        line(src,p1,p2,Scalar(255,0,255),1);
        Ar[i].pot.push_back(Point2f(-Ar[i].width*cos(Ar[i].angry)+EAstick[i].pot1.x,
                                    Ar[i].width*sin(Ar[i].angry)+EAstick[i].pot1.y));
        Ar[i].pot.push_back(Point2f(Ar[i].width*cos(Ar[i].angry)+EAstick[i].pot1.x,
                                    -Ar[i].width*sin(Ar[i].angry)+EAstick[i].pot1.y));
        Ar[i].pot.push_back(Point2f(Ar[i].width*cos(Ar[i].angry)+EAstick[i].pot2.x,
                                    -Ar[i].width*sin(Ar[i].angry)+EAstick[i].pot2.y));
        Ar[i].pot.push_back(Point2f(-Ar[i].width*cos(Ar[i].angry)+EAstick[i].pot2.x,
                                    Ar[i].width*sin(Ar[i].angry)+EAstick[i].pot2.y));

        Ar[i].DrawMoveArmor(src);
    }
    /******************************/


    imshow("src", src);
    waitKey(0);
    return 0;
}

