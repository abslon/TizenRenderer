#include "Instance.h"

using namespace Dali;
using namespace std;

Instance::Instance(Actor actor, btRigidBody* rigidBody)
{
    _actor = actor;
    _rigidBody = rigidBody;
}

void Instance::UpdateTransform()
{
    btTransform trans;
    _rigidBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    btQuaternion rot = trans.getRotation();

    //cout << pos.getX() << pos.getY() << pos.getZ() << endl;

    _actor.SetPosition(Vector3(pos.getX(), -pos.getY(), pos.getZ()));
    _actor.SetOrientation(Quaternion(rot.getW(), -rot.getX(), rot.getY(), -rot.getZ()));
    return;
}