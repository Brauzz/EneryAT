#ifndef ENERY_H
#define ENERY_H
#include <opencv2/opencv.hpp>
#define ACCEPT_TIME 2500
#define ROU1 100
#define ROU2 110
#define ARMOR_WIDTH 10

using namespace std;
using namespace cv;
extern Point2f EneryCenter;
//*******EneryAT
class EneryAT{
public:
    class MoveArmor{
    public:
        MoveArmor();

        vector<Point2f> pot;
        float angry;
        float width;
        void SetOn(int);
        void SetOff(int);
        void RandomSet(int);
        void DrawMoveArmor(Mat& img);
    };

    class EneryStick{
    public:
        EneryStick();

        float angry;
        float rou1;
        float rou2;

        Point2f pot1;
        Point2f pot2;
        void DrawEneryStick(Mat& img);
    };

    void getEneryATState();
    void EneryATCheck();
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
