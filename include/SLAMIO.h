#ifndef SLAMIO_H_
#define SLAMIO_H_

#include "TBSystem.h"

namespace
{
vector<double> mvCameraTimeline;
vector<Vector3> mvCameraPosition;
vector<Quaternion> mvCameraRotation;

vector<string> mvStereoCameraRGBName;
vector<Vector3> mvMapPoints;
}

void ReadCameraTrajectory();
string GetBackgroundPath(double timer);

#endif