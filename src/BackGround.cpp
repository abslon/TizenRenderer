#include "TBSystem.h"
#include "Shader.h"

int sensor = 0;
Actor mBackgroundActor;
TextureSet mBackgroundTextureSet;

Geometry CreateBackgroundGeometry()
{
    struct Vertex 
    {
        Vector2 vert;
        Vector2 texc;
    };

    Vertex backgroundVertices[] = {
        { Vector2(-1.0f, -1.0f), Vector2(0.0f, 1.0f) },
        { Vector2(-1.0f, 1.0f) , Vector2(0.0f, 0.0f) },
        { Vector2(1.0f, 1.0f)  , Vector2(1.0f, 0.0f) },
        { Vector2(1.0f, -1.0f) , Vector2(1.0f, 1.0f) },
        { Vector2(-1.0f, -1.0f) , Vector2(0.0f, 1.0f) },
        { Vector2(1.0f, 1.0f)  , Vector2(1.0f, 0.0f) },
    };

    PropertyBuffer vertexBuffer = PropertyBuffer::New( Property::Map()
                                                        .Add( "aPosition", Property::VECTOR2 )
                                                        .Add( "aTexCoord",  Property::VECTOR2 ) );
    vertexBuffer.SetData( backgroundVertices, sizeof(backgroundVertices) / sizeof(Vertex) );

    Geometry mBackgroundGeometry = Geometry::New();
    mBackgroundGeometry.AddVertexBuffer( vertexBuffer );
    mBackgroundGeometry.SetType( Geometry::TRIANGLES );
    return mBackgroundGeometry;
}

void DisplayBackground(string path, Geometry geo)
{
    PixelData pixels = SyncImageLoader::Load( path.c_str() );

    Texture texture = Texture::New( TextureType::TEXTURE_2D, pixels.GetPixelFormat(), pixels.GetWidth(), pixels.GetHeight() );
    texture.Upload( pixels, 0, 0, 0, 0, pixels.GetWidth(), pixels.GetHeight() );

    mBackgroundTextureSet = TextureSet::New();
    mBackgroundTextureSet.SetTexture( 0, texture );

    Shader mShaderBackground = LoadShaders("vertexBackground.glsl", "fragmentBackground.glsl");

    Renderer mBackgroundRenderer = Renderer::New(geo, mShaderBackground );
    mBackgroundRenderer.SetTextures( mBackgroundTextureSet );
    mBackgroundRenderer.SetProperty( Renderer::Property::DEPTH_INDEX, 2.0f );

    // Enables the depth test.
    mBackgroundRenderer.SetProperty( Renderer::Property::DEPTH_TEST_MODE, DepthTestMode::ON );

    // The fragment shader will run only is those pixels that have the max depth value.
    mBackgroundRenderer.SetProperty( Renderer::Property::DEPTH_FUNCTION, DepthFunction::LESS_EQUAL );

    Stage stage = Stage::GetCurrent();

    mBackgroundActor = Actor::New();
    mBackgroundActor.SetName( "Background" );
    mBackgroundActor.SetAnchorPoint( AnchorPoint::CENTER );
    mBackgroundActor.SetParentOrigin( ParentOrigin::CENTER );
    mBackgroundActor.SetPosition( CAMERA_DEFAULT_POSITION );
    mBackgroundActor.AddRenderer( mBackgroundRenderer );
    stage.Add( mBackgroundActor );
}

void CreateBackground(string path)
{
    Geometry geo = CreateBackgroundGeometry();
    DisplayBackground(path, geo);
}

void UpdateBackground(string path)
{
    PixelData pixels = SyncImageLoader::Load( path.c_str() );

    Texture texture = Texture::New( TextureType::TEXTURE_2D, pixels.GetPixelFormat(), pixels.GetWidth(), pixels.GetHeight() );
    texture.Upload( pixels, 0, 0, 0, 0, pixels.GetWidth(), pixels.GetHeight() );

    mBackgroundTextureSet.SetTexture( 0, texture );
    mBackgroundActor.GetRendererAt(0).SetTextures(mBackgroundTextureSet);
}

void SetSensor(int s)
{
    sensor = s;
}