#ifndef CAMERA_H
#define CAMERA_H

#include "../Common/GLee.h"
#include <GL/glu.h>
#include "../Common/amath.h"
#include "wx/gdicmn.h"
using namespace vector_math;
using namespace matrix_math;

/**
A Camera That Can Operate In Different Views
--Only Othographic Is Implemented ATM
*/

class Camera
{
    private:

    Vec4<float> pos_ortho;  //Position Vector for orthogonal camera
    Vec4<float> pos_persp;  //Position Vector for perspective camera
    float rotate2D;         //camera rotation (when using a ortho camera)
    double cameraMatrix[16];//camera matrix


    public:
                    ///Constructor
        Camera();
                    ///Destructor
        ~Camera();

        ////////////////////////////////
        //Set Camera View Perspectives//
        ////////////////////////////////

                         ///Setup 2d orthographic view
        void setup2D();
                         ///Setup 2.5d orthographic view
        void setup25D();
                         ///Setup 3d perspective view
        void setup3D();
                                         ///Viewport reshape
        void reshapeView(int w, int h);

        ///////////////////
        //Camera Movement//
        ///////////////////
                                         ///Camera Pan
        void cam2DPan(float x, float y);
                                         ///Camera Zoom
        void cam2DZoom(float zoom);
                                         ///Rotate Camera (In Degrees)
        void cam2DRotate(float r);

        ////////////////////////////
        //get Camera Location Data//
        ////////////////////////////

                                ///Get 2D camera position X
        float getXPos2D();
                                ///Get 2D camera position Y
        float getYPos2D();
                                ///Get 2D camera position Z
        float getZPos2D();
                                ///Get 2D camera Zoom
        float getZoomPos2D();
                                ///Get 2D camera pos
        Vec3<float> getPos2D();
                                    ///Get Camera Matrix (4x4)
        double * GetCameraMatrix();

        ///////////////////////////
        //Camera Utiliy Functions//
        ///////////////////////////

        //void fustrumPoints2D(int winWidth, int winHeight, Vec3<float> & fPt1, Vec3<float> & fPt2);
        //void pointInSpace2D(int mouseXPos, int mouseYPos, Vec3<float> & fPt);

        //////////////
        //Use Camera//
        //////////////
                                    ///Use Canera
        void useCamera();
};

#endif
