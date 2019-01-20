#ifndef SLAMIO_H_
#define SLAMIO_H_

#include "TBSystem.h"

extern vector<double> mvCameraTimeline;
extern vector<Vector3> mvCameraPosition;
extern vector<Quaternion> mvCameraRotation;

extern vector<string> mvStereoCameraRGBName;
extern vector<Vector3> mvMapPoints;

void ReadCameraTrajectory();
int SeqNumFromTimer(double timer);
string GetBackgroundPath(double timer);

#endif