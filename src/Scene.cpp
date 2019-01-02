#include "Scene.h"
#include "TBSystem.h"
#include "Primitives.h"
#include "Shader.h"

using namespace std;

namespace
{
const string TEXTURE_PATH = APP_RES_PATH + "images/wood.png";
const string TEXTURE_PATH_PLAIN = APP_RES_PATH + "images/floor.jpg";
const string TEXTURE_PATH_BALL = APP_RES_PATH + "images/012.jpg";

}

Shader LoadDefaultShader()
{
    Shader mShaderCube = LoadShaders("vertexPhong.glsl", "fragmentPhong.glsl");
    mShaderCube.RegisterProperty("uLightPos", Vector3(-1, -1, -1));
    mShaderCube.RegisterProperty("uViewPos", CAMERA_DEFAULT_POSITION);
    mShaderCube.RegisterProperty("uLightColor", Vector3(1, 1, 1));
    return mShaderCube;
}

void DefaultScene()
{
    Shader mShaderCube = LoadDefaultShader();
    Cube cb(TEXTURE_PATH, mShaderCube, Vector3(0.25, 0.25, 0.25));
    Plane p(TEXTURE_PATH_PLAIN, mShaderCube, Vector2(4, 4));
    Sphere ball(TEXTURE_PATH_BALL, mShaderCube, 0.5f);

    Instance* i1 = cb.CreateInstance(Vector3(0, 3, -6), Quaternion());
    Instance* i2 = p.CreateInstance(Vector3(0, -3, -6), Quaternion());
    Instance* i3 = ball.CreateInstance(Vector3(1.5f, 3, -6), Quaternion());

    i1->GetRigidBody()->setRestitution(0.3f);
    i2->GetRigidBody()->setFriction(0.5f);
    i2->GetRigidBody()->setMassProps(btScalar(0), btVector3(0, 0, 0));
}

void CreateSceneContents(int sceneNumber)
{
    switch(sceneNumber)
    {
    default:
        DefaultScene();
        break;
    }
}