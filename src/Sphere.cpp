#include "Primitives.h"

using namespace Dali;
using namespace Dali::Toolkit;
using namespace std;

Sphere::Sphere()
{
	SetGeometry();
	SetTextureSet();
	SetRenderer();
}

Sphere::Sphere(string texturePath, Shader& shader, float radius)
{
	_texturePath = texturePath;
	_shader = shader;
	_shapeSize = Vector3(radius * 2, radius * 2, radius * 2);
	SetGeometry();
	SetTextureSet();
	SetRenderer();
}

Instance* Sphere::CreateInstance(Vector3 position, Quaternion rotation)
{
	Actor _actor = Actor::New();
	_actor.SetAnchorPoint( AnchorPoint::CENTER );
	_actor.SetParentOrigin( ParentOrigin::CENTER );
	_actor.AddRenderer(_renderer);
	_actor.SetSize(_shapeSize);

	btRigidBody* planeRB = DynamicsWorld::GetInstance().CreateSphereRigidBody(_shapeSize.x / 2.0f,
				position, rotation);
	
	btTransform trans;
    planeRB->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    btQuaternion rot = trans.getRotation();

    _actor.SetPosition(Vector3(pos.getX(), -pos.getY(), pos.getZ()));
    _actor.SetOrientation(Quaternion(rot.getW(), -rot.getX(), rot.getY(), -rot.getZ()));

	Stage stage = Stage::GetCurrent();
	stage.Add( _actor );

	Instance* ins = new Instance(_actor, planeRB);
	DynamicsWorld::GetInstance().AddInstance(ins);
	return ins;
}

void Sphere::SetGeometry()
{
    PbrDemo::ObjLoader obj = PbrDemo::ObjLoader();
    string filedir = APP_RES_PATH + "models/biliard_ball.obj";
    ifstream file(filedir, ios::binary | ios::ate);
    vector<char> data;
    size_t size = file.tellg();
    data.resize(size);
    file.seekg(0, ios::beg);
    file.read(&data[0], size);
    obj.LoadObject(&data[0], size);
    _geometry = obj.CreateGeometry(7, true);
	return;
}

void Sphere::SetTextureSet()
{
	PixelData pixels = SyncImageLoader::Load( _texturePath );
	Texture texture = Texture::New( TextureType::TEXTURE_2D, pixels.GetPixelFormat(), pixels.GetWidth(), pixels.GetHeight() );
	texture.Upload( pixels, 0, 0, 0, 0, pixels.GetWidth(), pixels.GetHeight() );
	_textureSet = TextureSet::New();
	_textureSet.SetTexture( 0, texture );
	return;
}

void Sphere::SetRenderer()
{
	_renderer = Renderer::New( _geometry, _shader );
	_renderer.SetTextures( _textureSet );

	_renderer.SetProperty( Renderer::Property::DEPTH_INDEX, 1.0f );
	_renderer.SetProperty( Renderer::Property::FACE_CULLING_MODE, FaceCullingMode::BACK );
	_renderer.SetProperty( Renderer::Property::DEPTH_WRITE_MODE, DepthWriteMode::ON );
	return;
}