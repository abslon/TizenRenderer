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
		Stage stage = Stage::GetCurrent();
		stage.GetRootLayer().SetBehavior(Layer::LAYER_3D);

		// temperaly true
		mDebug = true;
		mdTime = 0;

		ReadCameraTrajectory();

		SetupCamera();

		// 0 means default scene contents
		CreateSceneContents(SceneName::Mappoint);

		string path = GetBackgroundPath(mdTime);
		CreateBackground(path);
		//CreateSkybox();

		// Connect to touch & key event signals
		stage.GetRootLayer().TouchSignal().Connect( this, &TizenBulletScene::OnTouch );
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
		if(!mDebug)
		{
			mdTime += 0.016;
			UpdateBackground(GetBackgroundPath(mdTime));
			mCamera.Update(mdTime);
			// DynamicsWorld::GetInstance().Update();
		}
		else
		{
			mCamera.OnDebugTick();
		}
		return true;
	}

	bool OnTouch( Actor actor, const TouchData& touch )
	{
		if(mDebug)
		{
			cout << "touched" << endl;
			mCamera.DebugRotate(actor, touch);
		}
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

			// press space to pause & debug
			else if(event.keyCode == 65)
			{
				
				mDebug = !mDebug;
			}

			// camera debug mode
			if(mDebug)
			{
				// WASDQE : Move
				if(event.keyCode == 25 || event.keyCode == 38 || event.keyCode == 39 
					|| event.keyCode == 40 || event.keyCode == 24 ||event.keyCode == 26 )
				{
					mCamera.DebugMove(event.keyCode);
				}
				// YHUJIK : Rotate with keys
				else if(event.keyCode == 29 || event.keyCode == 43 || event.keyCode == 30 
					|| event.keyCode == 44 || event.keyCode == 31 ||event.keyCode == 45 )
				{
					mCamera.DebugKeyRotate(event.keyCode);
				}
				// P : Print 
				else if(event.keyCode == 33)
				{
					mCamera.DebugPrint();
				}
				// G : Change Move mode
				else if(event.keyCode == 42)
				{
					mCamera.DeubgChangeMode();
				}
				// R : Reset
				else if(event.keyCode == 27)
				{
					mCamera.DebugReset();
				}	
			}
			// cout << "keycode: " << event.keyPressed + " " + event.keyPressedName + " " << event.keyCode << endl;
		}
	}

private:
	Application&  mApplication;
	// LookCamera mLCamera;
	MyCamera mCamera;

	Timer mTimer;
	double mdTime;
	bool mDebug;
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
