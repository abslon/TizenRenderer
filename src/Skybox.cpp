#include "Skybox.h"
#include "TBSystem.h"
#include "Shader.h"

using namespace Dali;
using namespace Dali::Toolkit;
using namespace std;

namespace
{
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

Geometry CreateSkyboxGeometry()
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

    Geometry skyboxGeometry = Geometry::New();
    skyboxGeometry.AddVertexBuffer( vertexBuffer );
    skyboxGeometry.SetType( Geometry::TRIANGLES );
    return skyboxGeometry;
}

void DisplaySkybox(Geometry skyboxGeometry)
{
    // Load skybox faces from file
    Texture texture = Texture::New( TextureType::TEXTURE_CUBE, Pixel::RGBA8888, SKYBOX_FACE_WIDTH, SKYBOX_FACE_HEIGHT );
    for (unsigned int i = 0; i < SKYBOX_FACE_COUNT; i++)
    {
        PixelData pixels = SyncImageLoader::Load( SKYBOX_FACES[i].c_str() );
        texture.Upload( pixels, CubeMapLayer::POSITIVE_X + i, 0, 0, 0, SKYBOX_FACE_WIDTH, SKYBOX_FACE_HEIGHT );
    }

    // create TextureSet
    TextureSet skyboxTextures = TextureSet::New();
    skyboxTextures.SetTexture( 0, texture );

    Shader shaderSkybox = LoadShaders("vertexSkybox.glsl", "fragmentSkybox.glsl");

    Renderer skyboxRenderer = Renderer::New( skyboxGeometry, shaderSkybox );
    skyboxRenderer.SetTextures( skyboxTextures );
    skyboxRenderer.SetProperty( Renderer::Property::DEPTH_INDEX, 2.0f );

    // Enables the depth test.
    skyboxRenderer.SetProperty( Renderer::Property::DEPTH_TEST_MODE, DepthTestMode::ON );

    // The fragment shader will run only is those pixels that have the max depth value.
    skyboxRenderer.SetProperty( Renderer::Property::DEPTH_FUNCTION, DepthFunction::LESS_EQUAL );

    Stage stage = Stage::GetCurrent();

    Actor skyboxActor = Actor::New();
    skyboxActor.SetName( "SkyBox" );
    skyboxActor.SetAnchorPoint( AnchorPoint::CENTER );
    skyboxActor.SetParentOrigin( ParentOrigin::CENTER );
    skyboxActor.SetPosition( CAMERA_DEFAULT_POSITION );
    skyboxActor.AddRenderer( skyboxRenderer );
    stage.Add( skyboxActor );
}

void CreateSkybox()
{
    Geometry skyboxGeometry = CreateSkyboxGeometry();
    DisplaySkybox(skyboxGeometry);
}