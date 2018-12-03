#include "enery.h"
#include "opencv2/opencv.hpp"


EneryAT::MoveArmor::MoveArmor()
{
    angry = 0;
    width = ARMOR_WIDTH;
    pot.push_back(Point(0,0));
}


EneryAT::EneryStick::EneryStick()
{
    angry = 3.14/2;
    rou1 = ROU1;
    rou2 = ROU2;
    pot1=Point(0,0);
    pot2=Point(0,0);

}

void EneryAT::EneryStick::DrawEneryStick(Mat& img)
{
    line(img,pot1,EneryCenter,Scalar(0,0,255),3);
    //ine(img,pot2,EneryCenter,Scalar(0,255,255),1);
}

void EneryAT::MoveArmor::DrawMoveArmor(Mat& img)
{
    for(int i=0;i<4;i++)
        line(img,pot[i],pot[(i+1)%4],Scalar(255,0,255),1);
}

//*******CLOCK
Eclock::Eclock(){

    EclockState = false;
    EclockTick = ACCEPT_TIME;

}

bool Eclock::EclockCheck()
{
    if(EclockTick>0&&EclockState==true)
        return true;
    else
        return false;
}

void Eclock::EclockReset()
{
    EclockTick = ACCEPT_TIME;
}

bool Eclock::EclockRun()
{
    if(EclockState==true)
    {
        EclockTick--;
        if(EclockCheck())
        {
            return 1;
        }else
        {
            EclockState=false;
            EclockReset();
            return 0;
        }
    }
}
