#ifndef SKYBOX_H_
#define SKYBOX_H_
#include "TBSystem.h"
#include "Shader.h"

namespace
{
const unsigned int SKYBOX_FACE_COUNT = 6;
const unsigned int SKYBOX_FACE_WIDTH  = 2048;
const unsigned int SKYBOX_FACE_HEIGHT = 2048;
const std::string SKYBOX_FACES[ SKYBOX_FACE_COUNT ] =
{
	APP_RES_PATH + "images/lake_right.jpg",
	APP_RES_PATH + "images/lake_left.jpg",
	APP_RES_PATH + "images/lake_top.jpg",
	APP_RES_PATH + "images/lake_bottom.jpg",
	APP_RES_PATH + "images/lake_back.jpg",
	APP_RES_PATH + "images/lake_front.jpg"
};
}
void CreateSkybox();
#endif