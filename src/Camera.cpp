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

    mCameraActor.SetPosition(position);
    mCameraActor.SetAnchorPoint( AnchorPoint::CENTER );
    mCameraActor.SetParentOrigin( ParentOrigin::CENTER );
    mCameraActor.SetPerspectiveProjection(screenSize);
    mCameraActor.SetNearClippingPlane( CAMERA_DEFAULT_NEAR );
    mCameraActor.SetFarClippingPlane( CAMERA_DEFAULT_FAR );
    mCameraActor.SetInvertYAxis(true);

    currSeqnum = 0;
    debugMoveMode = true;
}

void MyCamera::Update(double mdTimer)
{
    int seqnum = SeqNumFromTimer(mdTimer);
    currSeqnum = seqnum;

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
    currPos = mvCameraPosition[seqnum];
    currRot = mvCameraRotation[seqnum];
    debugPos = currPos;
    debugRot = currRot;
    // cout << "--------------------------------------------------------------------------------------------" << endl;
    // cout << "Camera Update" << endl;
    // cout << "seqnum : " << seqnum << endl;
    // cout << "position set : " << mvCameraPosition[seqnum] << endl;
    // cout << "rotation set : " << mvCameraRotation[seqnum].mVector << endl;
    // cout << "--------------------------------------------------------------------------------------------" << endl << endl;
}

void MyCamera::DebugMove(int moveDir)
{
    Vector3 front;
    Vector3 up;
    Vector3 left;
    Vector4 rot = debugRot.mVector;
    if(debugMoveMode)
    {
        front.x = 2 * (rot.x*rot.z + rot.w*rot.y);
        front.y = 2 * (rot.y*rot.z - rot.w*rot.x);
        front.z = 1 - 2 * (rot.x*rot.x + rot.y*rot.y);

        up.x = 2 * (rot.x*rot.y - rot.w*rot.z);
        up.y = 1 - 2 * (rot.x*rot.x + rot.z*rot.z);
        up.z = 2 * (rot.y*rot.z + rot.w*rot.x);

        left.x = 1 - 2 * (rot.y*rot.y + rot.z*rot.z);
        left.y = 2 * (rot.x*rot.y + rot.w*rot.z);
        left.z = 2 * (rot.x*rot.z - rot.w*rot.y);
    }
    else
    {
        front = Vector3(0, 0, 1);
        up = Vector3(0, 1, 0);
        left = Vector3(1, 0, 0);
    }

    switch(moveDir)
    {
    // w
    case 25:
        debugPos += front * 0.1f;
        break;
    // a
    case 38:
        debugPos += left * 0.1f;
        break;
    // s
    case 39:
        debugPos -= front * 0.1f;
        break;
    // d
    case 40:
        debugPos -= left * 0.1f;
        break;
    // q
    case 24:
        debugPos += up * 0.1f;
        break;
    // e
    case 26:
        debugPos -= up * 0.1f;
        break;
    }
    mCameraActor.SetPosition(debugPos);
}

void MyCamera::DebugRotate(Actor actor, const TouchData& touch)
{
    Stage stage = Stage::GetCurrent();

    for( int i = 0; i < (int)touch.GetPointCount() && i < 3; ++i )
    {
        Vector2 position( touch.GetScreenPosition( i ) );
        cout << "touch position: " << position << endl;

        // touch started
        if( touch.GetState( i ) == PointState::STARTED )
        {
            mOldTouchLookPosition = position;
        }
        else if( touch.GetState( i ) == PointState::FINISHED ||
                    touch.GetState( i ) == PointState::LEAVE ||
                    touch.GetState( i ) == PointState::INTERRUPTED
                    )
        {
            mScreenLookDelta = Vector2::ZERO;
            mOldTouchLookPosition = Vector2::ZERO;
        }
        else // on motion
        {
            mScreenLookDelta.x += ( position.x - mOldTouchLookPosition.x );
            mScreenLookDelta.y += ( position.y - mOldTouchLookPosition.y );
            mOldTouchLookPosition = position;
        }
    }
}

void MyCamera::DebugKeyRotate(int rotDir)
{
    Quaternion delta;
    switch(rotDir)
    {
    case 29:
        delta = Quaternion(Radian(Degree(1)), Vector3(1, 0, 0));
        break;
    case 43:
        delta = Quaternion(Radian(Degree(-1)), Vector3(1, 0, 0));
        break;
    case 30:
        delta = Quaternion(Radian(Degree(1)), Vector3(0, 1, 0));
        break;
    case 44:
        delta = Quaternion(Radian(Degree(-1)), Vector3(0, 1, 0));
        break;
    case 31:
        delta = Quaternion(Radian(Degree(1)), Vector3(0, 0, 1));
        break;
    case 45:
        delta = Quaternion(Radian(Degree(-1)), Vector3(0, 0, 1));
        break;
    }
    debugRot = delta * debugRot;
    mCameraActor.SetOrientation(debugRot);
}

void MyCamera::DebugReset()
{
    int seqnum = currSeqnum;
    debugPos = currPos;
    debugRot = currRot;
    mCameraActor.SetPosition(mvCameraPosition[seqnum]);
    mCameraActor.SetOrientation(mvCameraRotation[seqnum]);
}

void MyCamera::DeubgChangeMode()
{
    debugMoveMode = !debugMoveMode;
}

void MyCamera::DebugPrint()
{
    int seqnum = currSeqnum;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << "Camera Update" << endl;
    cout << "seqnum : " << seqnum << endl;
    cout << "seq position : " << mvCameraPosition[seqnum] << endl;
    cout << "seq rotation : " << mvCameraRotation[seqnum].mVector << endl;
    cout << "camera position : " << mCameraActor.GetCurrentPosition() << endl;
    cout << "camera rotation : " << mCameraActor.GetCurrentOrientation().mVector << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl << endl;
}

bool MyCamera::OnDebugTick()
{
    const float   CAMERA_SENSITIVITY        ( 90.0f );
    const float   CAMERA_VERTICAL_LIMIT     ( 80.0f );
    Vector2 mCameraYawPitch;
    Vector2 stageSize = Stage::GetCurrent().GetSize();

    // ---------------------------------------------------------------------
    // update rotation
    if(mScreenLookDelta.Length() > 0)
        cout << "delta: " << mScreenLookDelta << endl;
    Vector2 tmp( mScreenLookDelta );
    mScreenLookDelta = Vector2::ZERO;

    float yaw = ( (tmp.y / stageSize.x ) * CAMERA_SENSITIVITY );
    float pitch = ( (tmp.x / stageSize.y ) * CAMERA_SENSITIVITY );
    mCameraYawPitch.x -= yaw;
    mCameraYawPitch.y -= pitch;
    if( abs( mCameraYawPitch.x ) > CAMERA_VERTICAL_LIMIT )
    {
    mCameraYawPitch.x = CAMERA_VERTICAL_LIMIT * ((mCameraYawPitch.x < 0) ? -1.0f : 1.0f );
    }

    
    Quaternion rotX( Degree( mCameraYawPitch.x), Vector3( 1.0f, 0.0f, 0.0f ) );
    Quaternion rotY( Degree( mCameraYawPitch.y), Vector3( 0.0f, 1.0f, 0.0f ) );
    debugRot = ( rotY * rotX * debugRot );

    mCameraActor.SetOrientation( debugRot );

    return true;
}
