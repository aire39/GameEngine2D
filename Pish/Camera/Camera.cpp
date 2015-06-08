#include "Camera.h"

Camera::Camera()
{
    pos_ortho.setXYZW(0.0f, 0.0f, 0.0f, 1.0f);
    pos_persp.setXYZW(0.0f, 0.0f, 0.0f, 0.0f);
    rotate2D = 0.0f;
}

Camera::~Camera()
{
}


void Camera::setup2D()
{
    /**
    A Top View Where There is No Depth (Visually)
    */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -100, 100);

}

void Camera::setup25D()
{
    /**
    Uses A 3D Camera View But From A Top View With A Perspective
    */
    wxSize size = wxDefaultSize;
    glViewport(0, 0, (GLint)size.GetWidth(), (GLint)size.GetHeight());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90.0f, (GLfloat)size.GetWidth()/(GLfloat)size.GetHeight(), 0.01f, 10000.0f);

    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_LINE_SMOOTH );

}

void Camera::setup3D()
{
    /**
    Uses A 3D Camera
    */

    wxSize size = wxDefaultSize;
    glViewport(0, 0, (GLint)size.GetWidth(), (GLint)size.GetHeight());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)size.GetWidth()/(GLfloat)size.GetHeight(), 0.01f, 10000.0f);

    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_LINE_SMOOTH );

}


void Camera::reshapeView(int w, int h)
{
    /**
    Reshapes The Opengl ViewPort
    */
    glViewport(0, 0, (GLint) w, (GLint) h);
}



void Camera::cam2DPan(float x, float y)
{
    /**
    Pan Camera Across XY Axis
    */
    pos_ortho.setXYZW(x, y, 0.0f, pos_ortho.getW());
}

void Camera::cam2DZoom(float zoom)
{
    /**
    Zoom In/out
    */
    pos_ortho.setXYZW(pos_ortho.getX(), pos_ortho.getY(), 0.0f, zoom);
}

void Camera::cam2DRotate(float r)
{
    /**
    Rotate Camera (In Degrees)
    */
    rotate2D = r;
}

float Camera::getXPos2D()
{
    return pos_ortho.getX();
}


float Camera::getYPos2D()
{
    return pos_ortho.getY();
}


float Camera::getZPos2D()
{
    return pos_ortho.getZ();
}


float Camera::getZoomPos2D()
{
    return pos_ortho.getW();
}

Vec3<float> Camera::getPos2D()
{
    Vec3<float> pos;
    pos = pos_ortho;
    return pos;
}

double * Camera::GetCameraMatrix()
{
    cameraMatrix[13] *= -1.0; //need to invert y or the position will be wrong
    return cameraMatrix;
}

/*
void Camera::fustrumPoints2D(int winWidth, int winHeight, Vec3<float> & fPt1, Vec3<float> & fPt2)
{
    Vec3<float> tmp1;
    Vec3<float> tmp2;

    Mat4X4<double> projMatrix;
    Mat4X4<double> modelMatrix;
    int view[4];

    double x1=0.0, y1=0.0, z1=0.0;
    double x2=0.0, y2=0.0, z2=0.0;

    glGetDoublev( GL_PROJECTION_MATRIX, projMatrix.matrixA);
    glGetDoublev( GL_MODELVIEW_MATRIX , modelMatrix.matrixA);
    glGetIntegerv( GL_VIEWPORT, view);

    projMatrix.matrixA[10] = 1.0;
    modelMatrix.matrixA[10] = 1.0;

    int check_pt1 = false;
    int check_pt2 = false;

    check_pt1 = gluUnProject(0, 0, 0, modelMatrix.matrixA, projMatrix.matrixA, view, &x1, &y1, &z1);
    check_pt2 = gluUnProject(winWidth, winHeight, 0, modelMatrix.matrixA, projMatrix.matrixA, view, &x2, &y2, &z2);

    if(check_pt1 == 1 && check_pt2 == 1)
    {
        tmp1.setXYZ((float)x1, (float)y1, (float)z1);
        tmp2.setXYZ((float)x2, (float)y2, (float)z2);

        fPt1 = tmp1;
        fPt2 = tmp2;

        cout << "fustrum points succeeded!" << endl;
    }
    else
    {
        fPt1.setXYZ(0.0f, 0.0f, 0.0f);
        fPt2.setXYZ(0.0f, 0.0f, 0.0f);

        fPt1 = tmp1;
        fPt2 = tmp2;

        cout << "fustrum points failed!" << endl;
    }
}


void Camera::pointInSpace2D(int mouseXPos, int mouseYPos, Vec3<float> & fPt)
{
    Vec3<float> tmp;

    Mat4X4<double> projMatrix;
    Mat4X4<double> modelMatrix;
    int view[4];

    double x=0.0, y=0.0, z=0.0;

    glGetDoublev( GL_PROJECTION_MATRIX, projMatrix.matrixA);
    glGetDoublev( GL_MODELVIEW_MATRIX , modelMatrix.matrixA);
    glGetIntegerv( GL_VIEWPORT, view);

    projMatrix.matrixA[10] = 1.0;
    modelMatrix.matrixA[10] = 1.0;

    int check_pt1 = false;

    check_pt1 = gluUnProject(mouseXPos, mouseYPos, 0, modelMatrix.matrixA, projMatrix.matrixA, view, &x, &y, &z);

    if( check_pt1 )
    {
        tmp.setXYZ((float)x, (float)y, (float)z);
        fPt = tmp;

        //cout << "point in space succeeded!" << endl; //WORKS
    }
    else
    {
        fPt.setXYZ(0.0f, 0.0f, 0.0f);
        fPt = tmp;

        //cout << "point in space failed!" << endl; //WORKS
    }
}
*/

void Camera::useCamera()
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    glScalef(pos_ortho.getW(), pos_ortho.getW(), 1.0f);
    glRotatef(rotate2D, 0.0f, 0.0f, 1.0f);
    glTranslatef(pos_ortho.getX(), pos_ortho.getY(), pos_ortho.getZ());

    //gluLookAt(1000, -1000, 1000, 0, 0, 0, 0, 0, 1);

    glGetDoublev( GL_MODELVIEW_MATRIX, cameraMatrix );

}
