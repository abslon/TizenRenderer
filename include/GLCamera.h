#ifndef GL_CAMERA_H_
#define GL_CAMERA_H_

#include "TBSystem.h"

class GLCamera
{
public:
    GLCamera();
    void Initialise(const Dali::Vector3& position, Matrix3 CameraMat, Vector2 screenSize, float near, float far);
    void Update(double mdTimer);
    
    void SetPosition(Vector3 pos);
    Vector3 GetPosition();
    void SetRotation(Quaternion rot);
    Quaternion GetRotation();

    Matrix viewMat;
    Matrix projMat;

};

#endif