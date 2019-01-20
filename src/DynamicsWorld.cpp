#include "DynamicsWorld.h"


using namespace std;

DynamicsWorld::DynamicsWorld()
{
    _collisionConfiguration = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);
    _overlappingPairCache = new btDbvtBroadphase();
    _solver = new btSequentialImpulseConstraintSolver();
    _dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _overlappingPairCache, _solver, _collisionConfiguration);
    _dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void DynamicsWorld::Update()
{
    _dynamicsWorld->stepSimulation(UPDATE_INTERVAL / 1000.0f, 10);
    SyncRigidBodies();
}

void DynamicsWorld::AddInstance(Instance* instance)
{
    _worldInstances.push_back(instance); 
}

void DynamicsWorld::SyncRigidBodies()
{
    for (int i = 0; i < _worldInstances.size(); i++)
    {
        _worldInstances[i]->UpdateTransform();
        //_worldInstances[i]->UpdateUniforms(viewMat, projMat);
    }
}

btRigidBody* DynamicsWorld::CreateCubeRigidBody(Dali::Vector3 shapeSize, Dali::Vector3 position, 
        Dali::Quaternion rotation)
{
    btVector3 cubeSize = btVector3(shapeSize.x, shapeSize.y, shapeSize.z);
    btCollisionShape *shape = new btBoxShape(cubeSize);

    btTransform transform;
    transform.setIdentity();

    btScalar mass(1.0f);
    btVector3 localInertia(0, 0, 0);
    shape->calculateLocalInertia(mass, localInertia);

    transform.setOrigin(btVector3(position.x, position.y, position.z));
    Dali::Vector4 quaternion = rotation.AsVector();
    transform.setRotation(btQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w));

    btDefaultMotionState *motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
    rbInfo.m_restitution = 0.8f;
    rbInfo.m_friction = 0.8f;

    btRigidBody* _cubeRB = new btRigidBody(rbInfo);
    _dynamicsWorld->addRigidBody(_cubeRB);
    return _cubeRB;
}

btRigidBody* DynamicsWorld::CreateSphereRigidBody(float radius, Dali::Vector3 position, 
        Dali::Quaternion rotation)
{
    btCollisionShape *shape = new btSphereShape(radius);

    btTransform transform;
    transform.setIdentity();

    btScalar mass(1.0f);
    btVector3 localInertia(0, 0, 0);
    shape->calculateLocalInertia(mass, localInertia);

    transform.setOrigin(btVector3(position.x, position.y, position.z));
    Dali::Vector4 quaternion = rotation.AsVector();
    transform.setRotation(btQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w));

    btDefaultMotionState *motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
    rbInfo.m_restitution = 0.8f;
    rbInfo.m_friction = 0.8f;

    btRigidBody* _sphereRB = new btRigidBody(rbInfo);
    _dynamicsWorld->addRigidBody(_sphereRB);

    return _sphereRB;
}