#ifndef DYNAMICSWORLD_H_
#define DYNAMICSWORLD_H_

#include "TBSystem.h"
#include "Instance.h"
#include <btBulletDynamicsCommon.h>

class DynamicsWorld
{
public:
    static DynamicsWorld& GetInstance()
    {
        static DynamicsWorld* DW = new DynamicsWorld();
        return *DW;
    }
    void Update();
    void AddInstance(Instance* instance);
    void SyncRigidBodies();
    btRigidBody* CreateCubeRigidBody(Dali::Vector3 shapeSize, Dali::Vector3 position, 
        Dali::Quaternion rotation);
    btRigidBody* CreateSphereRigidBody(float radius, Dali::Vector3 position, 
        Dali::Quaternion rotation);
    btDiscreteDynamicsWorld* GetDynamicsWorld() { return _dynamicsWorld; }

private:
    DynamicsWorld();

	btSequentialImpulseConstraintSolver *_solver;
	btBroadphaseInterface *_overlappingPairCache;
	btCollisionDispatcher *_dispatcher;
	btDefaultCollisionConfiguration *_collisionConfiguration;
    btDiscreteDynamicsWorld *_dynamicsWorld;

    std::vector<Instance*> _worldInstances;
};

#endif /* DYNAMICSWORLD_H_ */