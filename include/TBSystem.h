/*
 * TBSystem.h
 *
 *  Created on: Nov 23, 2018
 *      Author: abslon
 */

#ifndef TBSYSTEM_H_
#define TBSYSTEM_H_

//#include <app_common.h>
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace Dali;
using namespace Dali::Toolkit;
using namespace std;

namespace
{
const std::string APP_RES_PATH( "/home/medialab/Documents/TizenRenderer/res/" );

const float CAMERA_DEFAULT_FOV(    60.0f );
const float CAMERA_DEFAULT_NEAR(    0.1f );
const float CAMERA_DEFAULT_FAR(  100.0f );
const Dali::Vector3 CAMERA_DEFAULT_POSITION( 0.0f, 0.0f, 1.0f );

const unsigned int UPDATE_INTERVAL = 16;

enum SensorType{
    Mono = 0,
    Stereo
};

}
const SensorType sensor = SensorType::Stereo;
#endif /* TBSYSTEM_H_ */
