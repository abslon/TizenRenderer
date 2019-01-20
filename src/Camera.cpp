#include "TBSystem.h"
#include "Camera.h"
#include "SLAMIO.h"

MyCamera::MyCamera()
{

}

void MyCamera::Initialise(const Dali::Vector3& position, Vector2 screenSize, float near, float far)
{
    Stage stage = Stage::GetCurrent();

    RenderTask renderTask = stage.GetRenderTaskList().GetTask( 0 );
    renderTask.SetCullMode( false ); // avoid frustum culling affecting the skybox
    mCameraActor = stage.GetRenderTaskList().GetTask(0).GetCameraActor();
    mCameraActor.SetName( "MyCamera" );

    mCameraActor.SetAnchorPoint( AnchorPoint::CENTER );
    mCameraActor.SetParentOrigin( ParentOrigin::CENTER );
    mCameraActor.SetPerspectiveProjection(screenSize);
    mCameraActor.SetNearClippingPlane( CAMERA_DEFAULT_NEAR );
    mCameraActor.SetFarClippingPlane( CAMERA_DEFAULT_FAR );
    mCameraActor.SetInvertYAxis(true);
}

void MyCamera::Update(double mdTimer)
{
    int seqnum = SeqNumFromTimer(mdTimer);
    

    // double a = mdTimer - mvCameraTimeline[seqnum];
    // double b = mvCameraTimeline[seqnum + 1] - mvCameraTimeline[seqnum];

    // double progress = a / b;
    // //cout << "progress: " << progress << endl;
    // Vector3 lPos = mvCameraPosition[seqnum] * (1 - progress) + 
    //     mvCameraPosition[seqnum + 1] * progress;
    // Quaternion lRot = Quaternion::Lerp(mvCameraRotation[seqnum], 
    //     mvCameraRotation[seqnum+1], progress);
    // mCameraActor.SetPosition(lPos);
    // mCameraActor.SetOrientation(lRot);

    mCameraActor.SetPosition(mvCameraPosition[seqnum]);
    mCameraActor.SetOrientation(mvCameraRotation[seqnum]);

    // cout << "--------------------------------------------------------------------------------------------" << endl;
    // cout << "Camera Update" << endl;
    // cout << "seqnum : " << seqnum << endl;
    // cout << "position set : " << mvCameraPosition[seqnum] << endl;
    // cout << "rotation set : " << mvCameraRotation[seqnum].mVector << endl;
    // cout << "--------------------------------------------------------------------------------------------" << endl << endl;
}
