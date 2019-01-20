#ifndef CAMERA_H_
#define CAMERA_H_

#include "TBSystem.h"

class MyCamera
{
public:
    MyCamera();
    void Initialise(const Dali::Vector3& position, Vector2 screenSize, float near, float far);
    void Update(double mdTimer);
    CameraActor GetCameraActor() {return mCameraActor;}
    
private:
    CameraActor mCameraActor;
};

#endif