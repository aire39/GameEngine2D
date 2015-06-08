/*///////////////////////
//                     //
//   SUPPORT FUNCTIONS //
//                     //
*////////////////////////

#include "../Common/glee.h"
#include "../Common/primitives.h"
#include "../Common/amath.h"

using namespace vector_math;

namespace supportFunctions
{

///Checks for openGL version
inline bool glVer(int maj, int min)
{
 const char *verstr = (const char *)glGetString(GL_VERSION);
 int *major = 0;
 int *minor = 0;
 sscanf(verstr, "%i.%i", &major, &minor);
 //cout << (int)major << " " << (int)minor  << endl;

 bool b;

 if( (int)major > maj )
 {
     b = true;
 }
 else
 {
     b = false;
 }

    return b;

}

///Creates box selection [Just visual representation]
inline GLuint * glBoxControl(Vec3<float> pt1, Vec3<float> pt2, Vec4<float> boxCFill, Vec4<float> boxCLine, float lineWidth = 1.0f, bool display = false, const Vec3<float> &camPos = Vec3<float>(0.0f, 0.0f, 0.0f))
{

    static GLuint boxBuffer[] = {0, 0};
    static bool initOnce = true;
    bool a = false;

    if(display)
    {
        //something about it needed to be flipped
        //immediate mode for quick testing

        glPushMatrix();

        glColor4f(boxCFill.getX(), boxCFill.getY(), boxCFill.getZ(), boxCFill.getW());
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

        glBegin( GL_QUADS );

            glVertex3f(pt2.getX(), -pt2.getY(), 0.0f);
            glVertex3f(pt1.getX(), -pt2.getY(), 0.0f); //
            glVertex3f(pt1.getX(), -pt1.getY(), 0.0f);
            glVertex3f(pt2.getX(), -pt1.getY(), 0.0f); //

        glEnd();

        glColor4f(boxCLine.getX(), boxCLine.getY(), boxCLine.getZ(), boxCLine.getW());
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(lineWidth);

        glBegin( GL_QUADS );

            glVertex3f(pt2.getX(), -pt2.getY(), 0.0f);
            glVertex3f(pt1.getX(), -pt2.getY(), 0.0f);
            glVertex3f(pt1.getX(), -pt1.getY(), 0.0f);
            glVertex3f(pt2.getX(), -pt1.getY(), 0.0f);

        glEnd();

        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

        glPopMatrix();
    }


    if(a)
    {

        CVert3<float> box[4];
        GLushort indices[6];

        box[0].setPos(pt2.getX(), pt2.getY(), 0.0f);
        box[1].setPos(pt2.getX(), pt1.getY(), 0.0f);
        box[2].setPos(pt1.getX(), pt1.getY(), 0.0f);
        box[3].setPos(pt1.getX(), pt2.getY(), 0.0f);


        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;


        if(boxBuffer[0] == 0 && boxBuffer[1] == 0)
            glGenBuffersARB(2, boxBuffer);

        if(initOnce)
        {
            glBindBufferARB( GL_ARRAY_BUFFER_ARB, boxBuffer[0]);
            glBufferDataARB( GL_ARRAY_BUFFER_ARB , 4*sizeof(*box), box, GL_STREAM_DRAW_ARB);
            glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

            glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, boxBuffer[1]);
            glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(GLushort)*6 , indices, GL_STREAM_DRAW_ARB);

            initOnce = false;
        }
        else
        {

            glBindBufferARB( GL_ARRAY_BUFFER_ARB, boxBuffer[0]);
            glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, boxBuffer[1]);

            glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, 4*sizeof(*box), box);

            glPushMatrix();

            glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

                glColor4f(boxCFill.getX(), boxCFill.getY(), boxCFill.getZ(), boxCFill.getW());
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0); //

                glColor4f(boxCLine.getX(), boxCLine.getY(), boxCLine.getZ(), boxCLine.getW());
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
                glLineWidth(lineWidth);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0); //

                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

            glPopMatrix();

        }

    }


    //////////////////////////////////////////
    //Set up blending to make highlight work//

    if(!glIsEnabled( GL_BLEND) )
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    if(!glIsEnabled( GL_ALPHA_TEST ) )
    {
        glEnable( GL_ALPHA_TEST );
        glAlphaFunc(GL_GREATER, 0);
    }

    if(glIsEnabled( GL_DEPTH_TEST ) )
        glDisable( GL_DEPTH_TEST );

    if(!glIsEnabled( GL_CULL_FACE ) )
        glDisable( GL_CULL_FACE ); //if using 3D it will enable to see the back faces of the 3d objects when in transparency

    return boxBuffer;
}


}
