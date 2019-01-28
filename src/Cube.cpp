/*
 * Cube.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: abslon
 */

#include "Primitives.h"

using namespace Dali;
using namespace Dali::Toolkit;
using namespace std;

Cube::Cube()
{
	SetGeometry();
	SetTextureSet();
	SetRenderer();
}

Cube::Cube(string texturePath, Shader& shader, Vector3 shapeSize)
{
	_texturePath = texturePath;
	_shader = shader;
	_shapeSize = shapeSize;
	SetGeometry();
	SetTextureSet();
	SetRenderer();
}

Instance* Cube::CreateInstance(Vector3 position, Quaternion rotation)
{
	Actor _actor = Actor::New();
	_actor.SetAnchorPoint( AnchorPoint::CENTER );
	_actor.SetParentOrigin( ParentOrigin::CENTER );
	_actor.AddRenderer(_renderer);
	_actor.SetSize(_shapeSize);

	btRigidBody* cubeRB = DynamicsWorld::GetInstance().CreateCubeRigidBody(_shapeSize, position, rotation);

	btTransform trans;
    cubeRB->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    btQuaternion rot = trans.getRotation();

    // _actor.SetPosition(Vector3(pos.getX(), pos.getY(), pos.getZ()));
    // _actor.SetOrientation(Quaternion(rot.getW(), -rot.getX(), rot.getY(), -rot.getZ()));
	_actor.SetPosition(position);
    _actor.SetOrientation(rotation);

	Stage stage = Stage::GetCurrent();
	stage.Add( _actor );

	Instance* ins = new Instance(_actor, cubeRB);
	DynamicsWorld::GetInstance().AddInstance(ins);
	return ins;
}

void Cube::SetGeometry()
{
	PropertyBuffer vertexBuffer = PropertyBuffer::New( Property::Map()
															   .Add( "aPosition", Property::VECTOR3 )
															   .Add( "aTexCoord", Property::VECTOR2 )
															   .Add( "aNormal", Property::VECTOR3 )  );
	vertexBuffer.SetData( cubeVertices, sizeof(cubeVertices) / sizeof(Vertex) );
	_geometry = Geometry::New();
	_geometry.AddVertexBuffer( vertexBuffer );
	_geometry.SetIndexBuffer( cubeIndex,
									  sizeof(cubeIndex)/sizeof(cubeIndex[0]) );
	_geometry.SetType( Geometry::TRIANGLES );
	return;
}

void Cube::SetTextureSet()
{
	PixelData pixels = SyncImageLoader::Load( _texturePath );
	Texture texture = Texture::New( TextureType::TEXTURE_2D, pixels.GetPixelFormat(), pixels.GetWidth(), pixels.GetHeight() );
	texture.Upload( pixels, 0, 0, 0, 0, pixels.GetWidth(), pixels.GetHeight() );
	_textureSet = TextureSet::New();
	_textureSet.SetTexture( 0, texture );
	return;
}

void Cube::SetRenderer()
{
	_renderer = Renderer::New( _geometry, _shader );
	_renderer.SetTextures( _textureSet );

	_renderer.SetProperty( Renderer::Property::DEPTH_INDEX, 1.0f );
	_renderer.SetProperty( Renderer::Property::FACE_CULLING_MODE, FaceCullingMode::BACK );
	_renderer.SetProperty( Renderer::Property::DEPTH_WRITE_MODE, DepthWriteMode::ON );
	return;
}




