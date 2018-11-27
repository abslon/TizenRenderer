/*
 * Object.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: abslon
 */
#include "Object.h"

using namespace Dali;

Instance* Object::CreateInstance(Dali::Vector3 position, Dali::Quaternion rotation)
{
	return new Instance();
}

void Object::SetGeometry()
{
	return;
}

void Object::SetTextureSet()
{
	return;
}

void Object::SetRenderer()
{
	return;
}






