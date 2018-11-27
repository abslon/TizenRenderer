/*
 * Object.h
 *
 *  Created on: Nov 23, 2018
 *      Author: abslon
 */

#ifndef OBJECT_H_
#define OBJECT_H_
#include "TBSystem.h"
#include <btBulletDynamicsCommon.h>
#include "Instance.h"

class Object
{
public:
	virtual Instance* CreateInstance(Dali::Vector3 position, Dali::Quaternion rotation);

	const char* GetName() { return _name; }
	void SetName(const char* name) { _name = name; }
	std::string GetTexturePath() { return _texturePath; }
	void SetTexturePath(std::string texturePath) { _texturePath = texturePath; }
	Dali::Vector3 GetShapeSize() { return _shapeSize; }
	void SetShapeSize(Dali::Vector3 shapeSize) { _shapeSize = shapeSize; }
	Dali::Shader GetShader() { return _shader; }
	void SetShader(Dali::Shader shader) { _shader = shader; }

	Dali::Geometry GetGeometry() { return _geometry; }
	virtual void SetGeometry();
	Dali::TextureSet GetTextureSet() { return _textureSet; }
	virtual void SetTextureSet();
	Dali::Renderer GetRenderer() { return _renderer; }
	virtual void SetRenderer();

protected:
	const char* _name;
	std::string _texturePath;
	Dali::Vector3 _shapeSize;
	Dali::Shader _shader;

	Dali::Geometry _geometry;
	Dali::TextureSet _textureSet;
	Dali::Renderer _renderer;
};


#endif /* OBJECT_H_ */
