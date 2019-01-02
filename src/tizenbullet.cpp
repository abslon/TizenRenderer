#include "TBSystem.h"
#include "Shader.h"
#include "look-camera.h"
#include "DynamicsWorld.h"
#include "Skybox.h"
#include "Scene.h"
#include "Background.h"

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
		application.GetWindow().SetSize(Window::WindowSize(640, 480));
		// Disable indicator.
		// It avoids reposition the camera to fit with the indicator height.
		Dali::Window winHandle = application.GetWindow();
		winHandle.ShowIndicator( Dali::Window::INVISIBLE );

		// Get a handle to the stage
		Stage stage = Stage::GetCurrent();
		stage.GetRootLayer().SetBehavior(Layer::LAYER_3D);

		SetupCamera();

		// 0 means default scene contents
		CreateSceneContents(SceneName::Default);

		string TEMP_BACK = APP_RES_PATH + "rgb_stereo/1311868164.363181.png";
		CreateBackground(TEMP_BACK);
		//CreateSkybox();

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
