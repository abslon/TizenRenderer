#include "TBSystem.h"
#include "Shader.h"
#include "look-camera.h"
#include "DynamicsWorld.h"
#include "Skybox.h"
#include "Scene.h"
#include "Background.h"
#include "SLAMIO.h"
#include "Camera.h"

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
		Dali::Window winHandle = application.GetWindow();
		winHandle.ShowIndicator( Dali::Window::INVISIBLE );

		Stage stage = Stage::GetCurrent();
		stage.GetRootLayer().SetBehavior(Layer::LAYER_3D);

		mPause = false;
		mdTime = 0;

		ReadCameraTrajectory();

		SetupCamera();

		// 0 means default scene contents
		CreateSceneContents(SceneName::Mappoint);

		string path = GetBackgroundPath(mdTime);
		CreateBackground(path);
		//CreateSkybox();

		// Connect to touch & key event signals
		stage.GetRootLayer().TouchedSignal().Connect( this, &TizenBulletScene::OnTouch );
		stage.KeyEventSignal().Connect( this, &TizenBulletScene::OnKeyEvent );
		
		DynamicsWorld::GetInstance().Update();

		mTimer = Timer::New(UPDATE_INTERVAL);
		mTimer.TickSignal().Connect(this, &TizenBulletScene::Update);
		mTimer.Start();
	}

	void SetupCamera()
	{
		// /* camera matrix setup
		// 	fx  s   cx
		// 	0   fy  cy
		// 	0   0   1
	 	//  */
		// Matrix3 cameraMat = Matrix3(520.908620, 0, 325.141442, 
		// 							0, 521.007327, 249.701764, 
		// 							0, 0, 1);
	
		mCamera.Initialise(CAMERA_DEFAULT_POSITION, Vector2(640, 480), CAMERA_DEFAULT_NEAR, CAMERA_DEFAULT_FAR);
		//mLCamera.Initialise(CAMERA_DEFAULT_POSITION, CAMERA_DEFAULT_FOV, CAMERA_DEFAULT_NEAR, CAMERA_DEFAULT_FAR );
	}

	bool Update()
	{
		if(!mPause)
		{
			mdTime += 0.016;
			UpdateBackground(GetBackgroundPath(mdTime));
			mCamera.Update(mdTime);
			// DynamicsWorld::GetInstance().Update();
		}
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

			//WASD
			else if(event.keyCode == 25 || event.keyCode == 38 || event.keyCode == 39 || event.keyCode == 40)
			{
				
			}

			else 
			{
				cout << "keycode: " << event.keyPressed + " " + event.keyPressedName + " " << event.keyCode << endl;
				//mPause = !mPause;
			}
		}
	}

private:
	Application&  mApplication;
	// LookCamera mLCamera;
	MyCamera mCamera;

	Timer mTimer;
	double mdTime;
	bool mPause;
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
