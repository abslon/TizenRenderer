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

void MapPointScene()
{
    Shader mShaderCube = LoadDefaultShader();
    Cube cb(TEXTURE_PATH, mShaderCube, Vector3(0.01, 0.01, 0.01));

    string point_path = APP_RES_PATH + "mappoints/StereoMapPoints.txt";
    ifstream in(point_path.c_str());
    char buf[1000];

    int l = 0;
    if (in.is_open()) 
    {
        while (!in.eof()) 
        {
            try
            {
                in.getline(buf, 1000);
                // ++l;
                // if (l < 10)
                //     continue;
                // else
                //     l = 0;
                stringstream s;
                s << buf;
                string token;

                Vector3 pos = Vector3();
                getline(s, token, ' ');
                pos.x = stof(token);
                getline(s, token, ' ');
                pos.y = stof(token);
                getline(s, token, ' ');
                pos.z = stof(token);
                //mvMapPoints.push_back(pos);
                cb.CreateInstance(pos, Quaternion())
                    ->GetRigidBody()->setMassProps(btScalar(0), btVector3(0, 0, 0));
            }
            catch (const std::invalid_argument& e)
            {
                cout << e.what() << endl;
                break; 
            }
        }
    } 
    else 
    {
        cout << "no point file!" << endl;
    }
}

void CreateSceneContents(int sceneNumber)
{
    switch(sceneNumber)
    {
    case SceneName::Mappoint:
        MapPointScene();
        break;
    default:
        DefaultScene();
        break;
    }
}