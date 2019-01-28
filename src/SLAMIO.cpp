#include "TBSystem.h"
#include "SLAMIO.h"
#include <btBulletDynamicsCommon.h>

vector<double> mvCameraTimeline;
vector<Vector3> mvCameraPosition;
vector<Quaternion> mvCameraRotation;
vector<string> mvStereoCameraRGBName;
vector<Vector3> mvMapPoints;

namespace
{

int recent_seqnum = 0;
const string SEQ_MONO_PATH = APP_RES_PATH + "rgb_mono/";
const string SEQ_STEREO_PATH = APP_RES_PATH;
}


void ReadMonoCameraTrajectory()
{
    string trajectoryURL = APP_RES_PATH + "trajectories/MonoKeyFrameTrajectory.txt";
    ifstream in(trajectoryURL.c_str());
    char buf[1000];

    if (in.is_open()) 
    {
        while (!in.eof()) 
        {
            in.getline(buf, 1000);
            stringstream s;
            s << buf;
            string token;

            getline(s, token, ' ');
            mvCameraTimeline.push_back(stod(token));

            Vector3 pos = Vector3();
            getline(s, token, ' ');
            pos.x = stof(token);
            getline(s, token, ' ');
            pos.y = -stof(token);
            getline(s, token, ' ');
            pos.z = stof(token);
            mvCameraPosition.push_back(pos);

            Vector4 quaternion = Vector4();
            getline(s, token, ' ');
            quaternion.x = stof(token);
            getline(s, token, ' ');
            quaternion.y = stof(token);
            getline(s, token, ' ');
            quaternion.z = stof(token);
            getline(s, token, ' ');
            quaternion.w = -stof(token);
            mvCameraRotation.push_back(Quaternion(quaternion));
        }
    } 
    else 
    {
        cout << "no trajectory file!" << endl;
    }
}

void ReadStereoCameraTrajectory()
{
    ifstream fAssociation;
    string associationURL = APP_RES_PATH + "trajectories/association.txt";
    fAssociation.open(associationURL.c_str());
    if (fAssociation.is_open()) 
    {
        bool isFirstLine = true;
        double firstTime = 0;
        while(!fAssociation.eof())
        {
            string s;
            getline(fAssociation,s);
            if(!s.empty())
            {
                stringstream ss;
                ss << s;
                double t;
                string sRGB;
                ss >> t;
                if(isFirstLine)
                {
                    isFirstLine = false;
                    firstTime = t;
                }
                mvCameraTimeline.push_back(t - firstTime);
                ss >> sRGB;
                mvStereoCameraRGBName.push_back(sRGB);
            }
        }
    }
    else 
    {
        cout << "no association file!" << endl;
    }
    

    string trajectoryURL = APP_RES_PATH + "trajectories/StereoCameraTrajectory.txt";
    ifstream in(trajectoryURL.c_str());
    char buf[1000];

    if (in.is_open()) 
    {
        while (!in.eof()) 
        {
            in.getline(buf, 1000);
            stringstream s;
            s << buf;
            string token;

            // remove the first part(timeline)
            getline(s, token, ' ');

            Vector3 pos = Vector3();
            getline(s, token, ' ');
            pos.x = stof(token);
            getline(s, token, ' ');
            pos.y = stof(token);
            getline(s, token, ' ');
            pos.z = stof(token);
            mvCameraPosition.push_back(pos);

            Vector4 quaternion = Vector4();
            getline(s, token, ' ');
            quaternion.x = stof(token);
            getline(s, token, ' ');
            quaternion.y = stof(token);
            getline(s, token, ' ');
            quaternion.z = stof(token);
            getline(s, token, ' ');
            quaternion.w = stof(token);
            mvCameraRotation.push_back(Quaternion(quaternion));

            cout << pos << " " << quaternion << endl;
            // btQuaternion rot = btQuaternion();
            // getline(s, token, ' ');
            // rot.setX(stof(token));
            // getline(s, token, ' ');
            // rot.setY(stof(token));
            // getline(s, token, ' ');
            // rot.setZ(stof(token));
            // getline(s, token, ' ');
            // rot.setW(stof(token));
            // Radian rad((float)rot.getAngle());
            // Vector3 axis(rot.getAxis().getX(), rot.getAxis().getY(), rot.getAxis().getZ());
            // mvCameraRotation.push_back(Quaternion(-rad,axis));
            // mvCameraRotation.push_back(Quaternion(-rot.getW(), rot.getX(), rot.getY(), rot.getZ()));
        }
    } 
    else 
    {
        cout << "no trajectory file!" << endl;
    }
}

void ReadCameraTrajectory()
{
    if(sensor == SensorType::Mono)
        ReadMonoCameraTrajectory();
    else if(sensor == SensorType::Stereo)
        ReadStereoCameraTrajectory();
}

int SeqNumFromTimer(double timer)
{
    for (int i = recent_seqnum; i < mvCameraTimeline.size(); i++)
    {
        if (mvCameraTimeline[i] >= timer)
        {
            if(i > recent_seqnum) recent_seqnum = i;
            break;
        }
    }
    return recent_seqnum;
}

string GetBackgroundPath(double timer)
{
    int seq_num = SeqNumFromTimer(timer);
    stringstream seqname;

    if(sensor == SensorType::Mono)
    {
        if(seq_num > 1521) seq_num = 1521;
        seqname << SEQ_MONO_PATH << setfill('0') << setw(4) << seq_num << ".jpg";
    }

    else if(sensor == SensorType::Stereo)
    {
        if(seq_num > 2965) seq_num = 2965;
        seqname << SEQ_STEREO_PATH << mvStereoCameraRGBName[seq_num];
    }

    return seqname.str();
}