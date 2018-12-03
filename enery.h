#ifndef ENERY_H
#define ENERY_H
#include <opencv2/opencv.hpp>
#define ACCEPT_TIME 1250
#define ROU1 100
#define ROU2 120
#define ARMOR_WIDTH 20

using namespace std;
using namespace cv;
extern Point2f EneryCenter;
//*******EneryAT
class EneryAT{
public:
    EneryAT();
    class MoveArmor{
    public:
        MoveArmor();

        float angry;
        float width;
        Scalar color;
        vector<Point2f> pot;

        void SetOn();
        void SetOff();
        void RandomSet();
        void DrawMoveArmor(Mat& img);
    };

    class EneryStick{
    public:
        EneryStick();

        float angry;
        float rou1;
        float rou2;
        Scalar color;
        Point2f pot1;
        Point2f pot2;
        void DrawEneryStick(Mat& img);
        void SetOn();
        void SetOff();
        void SetOning();
    };
    int EneryATstate;
    void getEneryATState();
    void EneryATCheck(int x,int y);
    void EneryReset();

};
//*********CLOCK
class Eclock{
public:
    Eclock();

    bool EclockState;
    int EclockTick;

    void EclockReset(void);
    bool EclockRun(void);
    bool EclockCheck(void);
};

#endif // ENERY_H
