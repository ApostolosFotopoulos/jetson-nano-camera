#include "camera.h"

Camera::Camera(){
  this->captureWidth = 1920;
  this->captureHeight = 1080;
  this->displayWidth = 960;
  this->displayHeight = 616;
  this->frameRate = 30;
  this->flipMethod = 2;
}
Camera::Camera(int captureWidth,int captureHeight,int displayWidth,int displayHeight,int frameRate,int flipMethod){
  this->captureWidth = captureWidth;
  this->captureHeight = captureHeight;
  this->displayWidth = displayWidth;
  this->displayHeight = displayHeight;
  this->frameRate = frameRate;
  this->flipMethod = flipMethod;
}

string Camera::stream(){
  return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + to_string(this->captureWidth) + ", height=(int)" +
          to_string(this->captureHeight) + ", format=(string)NV12, framerate=(fraction)" + to_string(this->frameRate) +
          "/1 ! nvvidconv flip-method=" + to_string(this->flipMethod) + " ! video/x-raw, width=(int)" + to_string(this->displayWidth) + ", height=(int)" +
          to_string(this->displayHeight) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}
