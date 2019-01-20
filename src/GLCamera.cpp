#include "TBSystem.h"
#include "GLCamera.h"
#include "SLAMIO.h"

GLCamera::GLCamera()
{

}

void GLCamera::Initialise(const Dali::Vector3& position, Matrix3 CameraMat, Vector2 screenSize, float near, float far)
{
    CameraActor mainCamera = Stage::GetCurrent().GetRenderTaskList().GetTask(0).GetCameraActor();
    mainCamera.SetPosition(position);
    ///mainCamera.SetOrientation()

    viewMat = Matrix();
    projMat = Matrix();

    viewMat.AsFloat()[15] = 1;
    projMat.AsFloat()[11] = 1;

    SetPosition(position);
\
    /* projection matrix setup
    {2*fx/W,0,0,0,
     2*s/W,2*fy/H,0,0,
     2*(cx/W)-1,2*(cy/H)-1,(zmax+zmin)/(zmax-zmin),1,
     0,0,2*zmax*zmin/(zmin-zmax),0}
    */
    CameraMat.AsFloat()[0];
    projMat.AsFloat()[0] = 2*CameraMat.AsFloat()[0]/screenSize.x;
    // projMat.AsFloat()[4] = 2*s/screenSize.x;    s = 0
    projMat.AsFloat()[5] = 2*CameraMat.AsFloat()[4]/screenSize.y;
    projMat.AsFloat()[2] = 2*(CameraMat.AsFloat()[6]/screenSize.x)-1;
    projMat.AsFloat()[6] = 2*(CameraMat.AsFloat()[7]/screenSize.y)-1;
    projMat.AsFloat()[10] = (far+near)/(far-near);
    projMat.AsFloat()[11] = 2*far*near/(near-far);

    // Stage stage = Stage::GetCurrent();

    // RenderTask renderTask = stage.GetRenderTaskList().GetTask( 0 );
    // renderTask.SetCullMode( false ); // avoid frustum culling affecting the skybox
    // mCameraActor = stage.GetRenderTaskList().GetTask(0).GetCameraActor();
    // mCameraActor.SetName( "Camera" );

    // mCameraActor.SetAnchorPoint( AnchorPoint::CENTER );
    // mCameraActor.SetParentOrigin( ParentOrigin::TOP_LEFT );
    // mCameraActor.SetPerspectiveProjection(screenSize);
    // mCameraActor.SetNearClippingPlane( CAMERA_DEFAULT_NEAR );
    // mCameraActor.SetFarClippingPlane( CAMERA_DEFAULT_FAR );
}

void GLCamera::Update(double mdTimer)
{
    int seqnum = SeqNumFromTimer(mdTimer);
    //cout << "seqnum: " << seqnum << endl;

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

    //mCameraActor.SetPosition(mvCameraPosition[seqnum]);
    //mCameraActor.SetOrientation(mvCameraRotation[seqnum]);

    SetPosition(mvCameraPosition[seqnum]);
    SetRotation(mvCameraRotation[seqnum]);
    cout << "set" << mvCameraRotation[seqnum].mVector <<endl; 

}

void GLCamera::SetPosition(Vector3 pos)
{
    viewMat.AsFloat()[12] = pos.x;
    viewMat.AsFloat()[13] = pos.y;
    viewMat.AsFloat()[14] = pos.z;
}

void GLCamera::SetRotation(Quaternion rot)
{
    cout << "set : " << rot.mVector << endl;
    float x = rot.mVector.p;
    float y = rot.mVector.q;
    float z = rot.mVector.r;
    float w = rot.mVector.s;

    float sqx = x*x;
    float sqy = y*y;
    float sqz = z*z;
    float sqw = w*w;

    // invs (inverse square length) is only required if quaternion is not already normalised
    float invs = 1 / (sqx + sqy + sqz + sqw);
    viewMat.AsFloat()[0] = ( sqx - sqy - sqz + sqw)*invs; // since sqw + sqx + sqy + sqz =1/invs*invs
    viewMat.AsFloat()[5] = (-sqx + sqy - sqz + sqw)*invs;
    viewMat.AsFloat()[10] = (-sqx - sqy + sqz + sqw)*invs;
    
    float tmp1 = x*y;
    float tmp2 = z*w;
    viewMat.AsFloat()[1] = 2.0 * (tmp1 + tmp2)*invs;
    viewMat.AsFloat()[4] = 2.0 * (tmp1 - tmp2)*invs;
    
    tmp1 = x*z;
    tmp2 = y*w;
    viewMat.AsFloat()[2] = 2.0 * (tmp1 - tmp2)*invs;
    viewMat.AsFloat()[8] = 2.0 * (tmp1 + tmp2)*invs;
    tmp1 = y*z;
    tmp2 = x*w;
    viewMat.AsFloat()[6] = 2.0 * (tmp1 + tmp2)*invs;
    viewMat.AsFloat()[9] = 2.0 * (tmp1 - tmp2)*invs;      
}

Vector3 GLCamera::GetPosition()
{
    Vector3 pos = Vector3(0, 0, 0);
    pos.x = viewMat.AsFloat()[12];
    pos.y = viewMat.AsFloat()[13];
    pos.z = viewMat.AsFloat()[14];
    return pos;
}

Quaternion GLCamera::GetRotation()
{
    float w = sqrtf(1.0 + viewMat.AsFloat()[0] + viewMat.AsFloat()[5] + viewMat.AsFloat()[10]) / 2.0;
	float w4 = (4.0 * w);
	float x = (viewMat.AsFloat()[6] - viewMat.AsFloat()[9]) / w4 ;
	float y = (viewMat.AsFloat()[8] - viewMat.AsFloat()[2]) / w4 ;
	float z = (viewMat.AsFloat()[1] - viewMat.AsFloat()[4]) / w4 ;
    return Quaternion(w, x, y, z);
}
