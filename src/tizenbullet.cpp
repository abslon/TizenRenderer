#include "TBSystem.h"
#include "Shader.h"
#include "look-camera.h"
#include "Primitives.h"
#include "Skybox.h"
#include <string>

using namespace Dali;
using namespace Dali::Toolkit;
using namespace std;

namespace
{
const string TEXTURE_PATH = APP_RES_PATH + "images/wood.png";
const string TEXTURE_PATH_PLAIN = APP_RES_PATH + "images/floor.jpg";
const string TEXTURE_PATH_BALL = APP_RES_PATH + "images/012.jpg";
}

class TizenBulletScene : public ConnectionTracker
{
public:
	TizenBulletScene( Application& application )
	: mApplication( application )
	{
		// Connect to the Application's init signal
		mApplication.InitSignal().Connect( this, &TizenBulletScene::Create );
	}

	// The init signal is received once (only) during the Application lifetime
	void Create( Application& application )
	{
		application.GetWindow().SetSize(Window::WindowSize(640, 360));
		// Disable indicator.
		// It avoids reposition the camera to fit with the indicator height.
		Dali::Window winHandle = application.GetWindow();
		winHandle.ShowIndicator( Dali::Window::INVISIBLE );

		// Get a handle to the stage
		Stage stage = Stage::GetCurrent();
		stage.GetRootLayer().SetBehavior(Layer::LAYER_3D);

		SetupCamera();

		CreateShaders();

		Cube cb(TEXTURE_PATH, mShaderCube, Vector3(0.25, 0.25, 0.25));
		Plane p(TEXTURE_PATH_PLAIN, mShaderCube, Vector2(4, 4));
		Sphere ball(TEXTURE_PATH_BALL, mShaderCube, 0.5f);

		Instance* i1 = cb.CreateInstance(Vector3(0, 3, -6), Quaternion());
		Instance* i2 = p.CreateInstance(Vector3(0, -3, -6), Quaternion());
		Instance* i3 = ball.CreateInstance(Vector3(1.5f, 3, -6), Quaternion());

		i1->GetRigidBody()->setRestitution(0.3f);
		i2->GetRigidBody()->setFriction(0.5f);
		i2->GetRigidBody()->setMassProps(btScalar(0), btVector3(0, 0, 0));

		CreateSkybox();

		// Connect to touch & key event signals
		stage.GetRootLayer().TouchedSignal().Connect( this, &TizenBulletScene::OnTouch );
		stage.KeyEventSignal().Connect( this, &TizenBulletScene::OnKeyEvent );
		
		mTimer = Timer::New(UPDATE_INTERVAL);
		mTimer.TickSignal().Connect(this, &TizenBulletScene::Update);
		mTimer.Start();
	}

	void SetupCamera()
	{
		Stage stage = Stage::GetCurrent();

		RenderTask renderTask = stage.GetRenderTaskList().GetTask( 0 );
		renderTask.SetCullMode( false ); // avoid frustum culling affecting the skybox

		mLCamera.Initialise(CAMERA_DEFAULT_POSITION, CAMERA_DEFAULT_FOV, CAMERA_DEFAULT_NEAR, CAMERA_DEFAULT_FAR );
	}

	void CreateShaders()
	{
		mShaderCube = LoadShaders("vertexPhong.glsl", "fragmentPhong.glsl");
		mShaderCube.RegisterProperty("uLightPos", Vector3(-1, -1, -1));
		mShaderCube.RegisterProperty("uViewPos", CAMERA_DEFAULT_POSITION);
		mShaderCube.RegisterProperty("uLightColor", Vector3(1, 1, 1));
	}

	bool Update()
	{
		DynamicsWorld::GetInstance().Update();
		return true;
	}

	bool OnTouch( Actor actor, const TouchEvent& event )
	{
		return true;
	}

	void OnKeyEvent( const KeyEvent& event )
	{
		if( event.state == KeyEvent::Down )
		{
			if( IsKey( event, DALI_KEY_ESCAPE ) || IsKey( event, DALI_KEY_BACK ) )
			{
				mApplication.Quit();
			}
		}
	}

private:
	Application&  mApplication;
	LookCamera mLCamera;
	CameraActor mACamera;

	Shader mShaderCube;

	Timer mTimer;
};


// Entry point for Tizen applications
//
int main( int argc, char **argv )
{
	Application application = Application::New( &argc, &argv );
	TizenBulletScene test( application );
	application.MainLoop();
	return 0;
}
