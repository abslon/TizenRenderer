#ifndef CAMERA_H_
#define CAMERA_H_

#include "TBSystem.h"

class MyCamera
{
public:
    MyCamera();
    void Initialise(const Vector3& position, Vector2 screenSize, float near, float far);
    void Update(double mdTimer);
    CameraActor GetCameraActor() {return mCameraActor;}
    void DebugMove(int moveDir);
    void DebugReset();
    void DebugRotate(Actor actor, const TouchData& touch);
    void DebugKeyRotate(int rotDir);
    void DeubgChangeMode();
    void DebugPrint();
    bool OnDebugTick();
    
private:
    int currSeqnum;
    Vector3 currPos;
    Quaternion currRot;
    CameraActor mCameraActor;
    Vector2 mScreenLookDelta; 
    Vector2 mOldTouchLookPosition;
    // true : moves like FPP controller
    // false : moves in 3DOF
    bool debugMoveMode;
    Vector3 debugPos;
    Quaternion debugRot;
};

#endif