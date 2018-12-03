#include "enery.h"
#include "opencv2/opencv.hpp"

//**********ARMOR
EneryAT::MoveArmor::MoveArmor()
{
    angry = 0;
    width = ARMOR_WIDTH;
    color = Scalar::all(255);

    pot.push_back(Point(0,0));
}

void EneryAT::MoveArmor::DrawMoveArmor(Mat& img)
{
    for(int i=0;i<4;i++)
        line(img,pot[i],pot[(i+1)%4],color,3);
}

void EneryAT::MoveArmor::RandomSet()
{


}

void EneryAT::MoveArmor::SetOn()
{
    color = Scalar(0,0,255);
}

void EneryAT::MoveArmor::SetOff()
{
    color = Scalar(255,255,255);
}


//**********STICK
EneryAT::EneryStick::EneryStick()
{
    angry = 3.14/2;
    rou1 = ROU1;
    rou2 = ROU2;
    color = Scalar::all(255);
    pot1=Point(0,0);
    pot2=Point(0,0);

}

void EneryAT::EneryStick::DrawEneryStick(Mat& img)
{
    line(img,pot1,EneryCenter,color,3);
    //ine(img,pot2,EneryCenter,Scalar(0,255,255),1);
}

void EneryAT::EneryStick::SetOn()
{
    color = Scalar(0,0,255);
}

void EneryAT::EneryStick::SetOff()
{
    color = Scalar::all(255);
}

void EneryAT::EneryStick::SetOning()
{
   color = Scalar(255,0,255);
}

//*********AT
EneryAT::EneryAT()
{
    EneryATstate = 0;
}

void EneryAT::EneryATCheck(int x, int y)
{

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
    else
    {
        return 1;
    }
}
