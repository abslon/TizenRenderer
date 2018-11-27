#include "TBSystem.h"
#include "Shader.h"
#include "look-camera.h"
#include "Primitives.h"
#include <string>

using namespace Dali;
using namespace Dali::Toolkit;
using namespace std;

namespace
{
const string TEXTURE_PATH = APP_RES_PATH + "images/wood.png";
const string TEXTURE_PATH_SPHERE = APP_RES_PATH + "images/billiard_art_ball_texture.png";
const string TEXTURE_PATH_PLAIN = APP_RES_PATH + "images/floor.jpg";

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

class TizenBulletScene : public ConnectionTracker
{
public:
	TizenBulletScene( Application& application )
	: mApplication( application )
	{
		// Connect to the Application's init signal
		mApplication.InitSignal().Connect( this, &TizenBulletScene::Create );
	}

	~TizenBulletScene()
	{
		// Nothing to do here
	}

	// The init signal is received once (only) during the Application lifetime
	void Create( Application& application )
	{
		// Disable indicator.
		// It avoids reposition the camera to fit with the indicator height.
		Dali::Window winHandle = application.GetWindow();
		winHandle.ShowIndicator( Dali::Window::INVISIBLE );

		// Get a handle to the stage
		Stage stage = Stage::GetCurrent();
		stage.SetBackgroundColor( Color::WHITE );

		SetupCamera();

		CreateShaders();

		Cube cb(TEXTURE_PATH, mShaderCube, Vector3(0.25, 0.25, 0.25));
		Plane p(TEXTURE_PATH_PLAIN, mShaderCube, Vector2(4, 4));
		Sphere s(TEXTURE_PATH_SPHERE, mShaderCube, 0.4f);

		Instance* i1 = cb.CreateInstance(Vector3(0, 3, -6), Quaternion());
		Instance* i2 = p.CreateInstance(Vector3(0, -3, -6), Quaternion());
		Instance* i3 = s.CreateInstance(Vector3(-1.5f, 3, -6), Quaternion());

		Instance* light = cb.CreateInstance(Vector3(1, 5, -8), Quaternion());

		i1->GetRigidBody()->setRestitution(0.3f);
		i2->GetRigidBody()->setFriction(0.5f);
		i2->GetRigidBody()->setMassProps(btScalar(0), btVector3(0, 0, 0));
		i3->GetRigidBody()->setRestitution(0);

		light->GetRigidBody()->setMassProps(btScalar(0), btVector3(0, 0, 0));

		CreateSkyboxGeometry();
		DisplaySkybox();

		stage.GetRootLayer().SetBehavior(Layer::LAYER_3D);

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

		mCamera.Initialise(CAMERA_DEFAULT_POSITION, CAMERA_DEFAULT_FOV, CAMERA_DEFAULT_NEAR, CAMERA_DEFAULT_FAR );
	}

	void CreateShaders()
	{
		mShaderCube = LoadShaders("vertexPhong.glsl", "fragmentPhong.glsl");
		//mShaderCube = LoadShaders("vertexDiffuse.glsl", "fragmentDiffuse.glsl");
		mShaderCube.RegisterProperty("uLightPos", Vector3(1, -5, -8));
		mShaderCube.RegisterProperty("uViewPos", CAMERA_DEFAULT_POSITION);
		mShaderCube.RegisterProperty("uLightColor", Vector3(1, 1, 1));
		mShaderSkybox = LoadShaders("vertexSkybox.glsl", "fragmentSkybox.glsl");

	}

	void CreateSkyboxGeometry()
	{
		struct Vertex
		{
			Vector3 aPosition;
		};

		Vertex skyboxVertices[] = {
			// back
			{ Vector3(  -1.0f,  1.0f, -1.0f ) },
			{ Vector3(  -1.0f, -1.0f, -1.0f ) },
			{ Vector3(   1.0f, -1.0f, -1.0f ) },
			{ Vector3(   1.0f, -1.0f, -1.0f ) },
			{ Vector3(   1.0f,  1.0f, -1.0f ) },
			{ Vector3(  -1.0f,  1.0f, -1.0f ) },

			// left
			{ Vector3(  -1.0f, -1.0f,  1.0f ) },
			{ Vector3(  -1.0f, -1.0f, -1.0f ) },
			{ Vector3(  -1.0f,  1.0f, -1.0f ) },
			{ Vector3(  -1.0f,  1.0f, -1.0f ) },
			{ Vector3(  -1.0f,  1.0f,  1.0f ) },
			{ Vector3(  -1.0f, -1.0f,  1.0f ) },

			// right
			{ Vector3(   1.0f, -1.0f, -1.0f ) },
			{ Vector3(   1.0f, -1.0f,  1.0f ) },
			{ Vector3(   1.0f,  1.0f,  1.0f ) },
			{ Vector3(   1.0f,  1.0f,  1.0f ) },
			{ Vector3(   1.0f,  1.0f, -1.0f ) },
			{ Vector3(   1.0f, -1.0f, -1.0f ) },

			// front
			{ Vector3(  -1.0f, -1.0f,  1.0f ) },
			{ Vector3(  -1.0f,  1.0f,  1.0f ) },
			{ Vector3(   1.0f,  1.0f,  1.0f ) },
			{ Vector3(   1.0f,  1.0f,  1.0f ) },
			{ Vector3(   1.0f, -1.0f,  1.0f ) },
			{ Vector3(  -1.0f, -1.0f,  1.0f ) },

			// botton
			{ Vector3(  -1.0f,  1.0f, -1.0f ) },
			{ Vector3(   1.0f,  1.0f, -1.0f ) },
			{ Vector3(   1.0f,  1.0f,  1.0f ) },
			{ Vector3(   1.0f,  1.0f,  1.0f ) },
			{ Vector3(  -1.0f,  1.0f,  1.0f ) },
			{ Vector3(  -1.0f,  1.0f, -1.0f ) },

			// top
			{ Vector3(  -1.0f, -1.0f, -1.0f ) },
			{ Vector3(  -1.0f, -1.0f,  1.0f ) },
			{ Vector3(   1.0f, -1.0f, -1.0f ) },
			{ Vector3(   1.0f, -1.0f, -1.0f ) },
			{ Vector3(  -1.0f, -1.0f,  1.0f ) },
			{ Vector3(   1.0f, -1.0f,  1.0f ) }
		};

		PropertyBuffer vertexBuffer = PropertyBuffer::New( Property::Map()
														   .Add( "aPosition", Property::VECTOR3 ) );
		vertexBuffer.SetData( skyboxVertices, sizeof(skyboxVertices) / sizeof(Vertex) );

		mSkyboxGeometry = Geometry::New();
		mSkyboxGeometry.AddVertexBuffer( vertexBuffer );
		mSkyboxGeometry.SetType( Geometry::TRIANGLES );
	}

	/**
	* Display a skybox surrounding the camera
	*/
	void DisplaySkybox()
	{
		// Load skybox faces from file
		Texture texture = Texture::New( TextureType::TEXTURE_CUBE, Pixel::RGBA8888, SKYBOX_FACE_WIDTH, SKYBOX_FACE_HEIGHT );
		for (unsigned int i = 0; i < SKYBOX_FACE_COUNT; i++)
		{
		  PixelData pixels = SyncImageLoader::Load( SKYBOX_FACES[i].c_str() );
		  texture.Upload( pixels, CubeMapLayer::POSITIVE_X + i, 0, 0, 0, SKYBOX_FACE_WIDTH, SKYBOX_FACE_HEIGHT );
		}

		// create TextureSet
		mSkyboxTextures = TextureSet::New();
		mSkyboxTextures.SetTexture( 0, texture );

		mSkyboxRenderer = Renderer::New( mSkyboxGeometry, mShaderSkybox );
		mSkyboxRenderer.SetTextures( mSkyboxTextures );
		mSkyboxRenderer.SetProperty( Renderer::Property::DEPTH_INDEX, 2.0f );

		// Enables the depth test.
		mSkyboxRenderer.SetProperty( Renderer::Property::DEPTH_TEST_MODE, DepthTestMode::ON );

		// The fragment shader will run only is those pixels that have the max depth value.
		mSkyboxRenderer.SetProperty( Renderer::Property::DEPTH_FUNCTION, DepthFunction::LESS_EQUAL );

		Stage stage = Stage::GetCurrent();

		mSkyboxActor = Actor::New();
		mSkyboxActor.SetName( "SkyBox" );
		mSkyboxActor.SetAnchorPoint( AnchorPoint::CENTER );
		mSkyboxActor.SetParentOrigin( ParentOrigin::CENTER );
		mSkyboxActor.SetPosition( CAMERA_DEFAULT_POSITION );
		mSkyboxActor.AddRenderer( mSkyboxRenderer );
		stage.Add( mSkyboxActor );
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

			if( IsKey(event, DALI_KEY_BRIGHTNESS_UP))
			{
				
			}
		}
	}

private:
	Application&  mApplication;
	LookCamera mCamera;

	Shader mShaderCube;
	Shader mShaderSkybox;

	Geometry mSkyboxGeometry;
	TextureSet mSkyboxTextures;
	Renderer mSkyboxRenderer;
	Actor mSkyboxActor;

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
