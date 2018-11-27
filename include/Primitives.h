#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_
#include "Object.h"
#include "Geometry.h"
#include "Instance.h"
#include "DynamicsWorld.h"
#include "obj-loader.h"

class Cube : public Object
{
public:
	Cube();
	Cube(std::string texturePath, Dali::Shader& shader, Dali::Vector3 shapeSize);
	Instance* CreateInstance(Dali::Vector3 position, Dali::Quaternion rotation);
	void SetGeometry();
	void SetTextureSet();
	void SetRenderer();
};

class Plane : public Object
{
public:
	Plane();
	Plane(std::string texturePath, Dali::Shader& shader, Dali::Vector2 shapeSize);
	Instance* CreateInstance(Dali::Vector3 position, Dali::Quaternion rotation);
	void SetGeometry();
	void SetTextureSet();
	void SetRenderer();
};

class Sphere : public Object
{
public:
	Sphere();
	Sphere(std::string texturePath, Dali::Shader& shader, float radius);
	Instance* CreateInstance(Dali::Vector3 position, Dali::Quaternion rotation);
	void SetGeometry();
	void SetTextureSet();
	void SetRenderer();
};

#endif /* PRIMITIVES_H_ */
