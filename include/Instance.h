#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "TBSystem.h"
#include <btBulletDynamicsCommon.h>

class Instance 
{
public:
    Instance() {}
    Instance(Dali::Actor actor, btRigidBody* rigidBody);

    void UpdateTransform();

    Dali::Actor GetActor() { return _actor; }
    btRigidBody* GetRigidBody() { return _rigidBody; }

private:
    Dali::Actor _actor;
    btRigidBody* _rigidBody;
};

#endif /* INSTANCE_H_ */