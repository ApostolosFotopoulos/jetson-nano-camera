#ifndef CAMERA_H
#define CAMERA_H
#include <string>

using namespace std;

class Camera{
public:
    Camera();
    Camera(int captureWidth,int captureHeight,int displayWidth,int displayHeight,int frameRate,int flipMethod);
    string stream();
private:
    int captureWidth;
    int captureHeight;
    int displayWidth;
    int displayHeight;
    int frameRate;
    int flipMethod;
};
#endif
