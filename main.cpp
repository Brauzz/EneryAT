#include <opencv2/opencv.hpp>
#include <iostream>
#include <enery.h>
#define DELAY_TIME 1
#define PI 3.14159
using namespace cv;
using namespace std;
RNG rng((unsigned)time(nullptr));
EneryAT::MoveArmor Ar[5];
EneryAT::EneryStick EAstick[5];
Eclock clocks;

vector<int> WaitAttack;
vector<int> Attacked;
vector<Point2f> Target;
Point2f EneryCenter = Point2f(320,240);
int dir = 1;//1 is clockwise /-1 is anticlockwise.
bool InitState = 0;//0 is mean not init/ 1 is mean init
int WaitIndex;
void RandomSet()
{
    if(WaitAttack.size()!=0){
        int RngNum = rng.uniform(0,WaitAttack.size());
        WaitIndex = WaitAttack.at(RngNum);
        WaitAttack.erase(WaitAttack.begin()+RngNum);
        //Attacked.push_back(WaitIndex);
        Ar[WaitIndex].SetOn();
        EAstick[WaitIndex].SetOning();
        clocks.EclockReset();
    }
}

static void onMouse(int event, int x, int y, int, void*)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        int inc = pointPolygonTest(Ar[WaitIndex].pot,Point2f(x,y),0);
        {
//        int a = (Ar[WaitIndex].pot[2].x-Ar[WaitIndex].pot[1].x)
//                *(y-Ar[WaitIndex].pot[1].y)
//                -(Ar[WaitIndex].pot[2].x-Ar[WaitIndex].pot[1].x)
//                *(y-Ar[WaitIndex].pot[2].y);
//        int b = (x-Ar[WaitIndex].pot[3].x)
//                *(Ar[WaitIndex].pot[4].y-Ar[WaitIndex].pot[3].y)
//                -(Ar[WaitIndex].pot[4].x-Ar[WaitIndex].pot[3].x)
//                *(y-Ar[WaitIndex].pot[3].y);
//        int c = (x-Ar[WaitIndex].pot[1].x)
//                *(Ar[WaitIndex].pot[4].y-Ar[WaitIndex].pot[1].y)
//                -(Ar[WaitIndex].pot[4].x-Ar[WaitIndex].pot[1].x)
//                *(y-Ar[WaitIndex].pot[1].y);
//        int d = (x-Ar[WaitIndex].pot[2].x)
//                *(Ar[WaitIndex].pot[3].y-Ar[WaitIndex].pot[2].y)
//                -(Ar[WaitIndex].pot[3].x-Ar[WaitIndex].pot[2].x)
//                *(y-Ar[WaitIndex].pot[2].y);
//        if(a*b<=0&&c*d<=0)
//            cout<<"1"<<endl;
//        else
//            cout<<"0"<<endl;
        }

        if(inc==1)
        {
            EAstick[WaitIndex].SetOn();
            RandomSet();
            clocks.EclockState = 1;
        }

    }
}

int main(int argc,char** argv)
{
    Mat src = Mat::zeros(480,640,CV_32FC3);
    namedWindow("src", CV_WINDOW_AUTOSIZE);

    for(int i=0;i<5;i++)
        WaitAttack.push_back(i);

    setMouseCallback("src", onMouse, nullptr);
    RandomSet();
    //while
    for(;;)
    {
        src = Scalar::all(0);
        for(int i=0;i<5;i++)
        {
            //draw enery stick
            if(!InitState)
                EAstick[i].angry = PI/2 + i*2*PI/5;

            else
                EAstick[i].angry = EAstick[i].angry - dir*PI/1500;

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

            Ar[i].pot.clear();
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
        if(!clocks.EclockRun())
        {
            for(int i=0;i<5;i++)
            {
                EAstick[i].SetOff();
                Ar[i].SetOff();
            }

            WaitAttack.clear();
            for(int i=0;i<5;i++)
                WaitAttack.push_back(i);
            RandomSet();
        }

        InitState = 1;
        imshow("src", src);
        if(waitKey(DELAY_TIME)>0)
            return 0;
    }
}

