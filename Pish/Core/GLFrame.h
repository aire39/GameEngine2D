#ifndef GLFRAME_H
#define GLFRAME_H

#include "../Common/GLee.h"
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include <wx/timer.h>
#include <wx/msgdlg.h>
#include <wx/thread.h>

#include <wx/frame.h>
#include <wx/image.h>

#include "../Common/UtilityFunctions.h"
#include "../Common/amath.h"
#include "../Camera/Camera.h"
#include "../Common/frameEvent.h"
#include "../Core/Sprite.h"
#include "../Management/ShaderMng.h"
#include "../Management/entityManager.h"
#include "../Management/texMng.h"

//Used for console info
#include <iostream>
using namespace std;

//Test Include Area For Testing New Graphics
//#include "../Core/PSysExplode.h"
//#include "../Core/PSysSpray.h"
#include "../Common/GApp.h"

class GLFrame : public wxGLCanvas
{
    DECLARE_EVENT_TABLE()

    //test
    //Particles * psys;

    private:
        bool AppMod;
        wxWindow    * m_parent;
        wxGLContext * opengl_context;

        propertyWindow   * property_window;

        ////////////////////////////////////////////
        bool t_access;       ///Set events active when entering window and inactive when leaving window

        Entity * picked_entity;
        Entity * picked_entity_sub;
        Entity * entity_highlight;

        std::vector<entityManager*> * scene_manager; ///Draw Manager( The Real One: WIP Not completely usable)
        texMng                      * texture_manager;

        bool SAnim;             ///Start/Stop animation for function (Only have one function that actually uses this)
        bool paintMode;
        bool tileEditable;

        wxLongLong tickBefore;  ///Store previous time tick
        wxString sfps;          ///Store fps as string (may not really be needed)
        Text * statistic_text;


        Camera * camera;     ///Dimensional aspect settings 2d/3d

        int   mStartX;     ///Store first click X
        int   mStartY;     ///Store first click Y
        float mLastX;      ///Store last click X
        float mLastY;      ///Store last click X
        float mTransX;     ///Store translation from click X
        float mTransY;     ///Store translation from click Y

        float cZoom;         ///Stores Current positioin of zoom
        float pZoom;         ///Stores last  click position for zoom
        float sZoom;         ///Stores start click position for zoom

        ShaderMng shaderMng; ///Shader management object

        frameEvent * frame_event;

        int GridX, GridY;
        float Grid_Spacing;
        void RenderGrid(int row=20, int col=20);
        void RenderHighlight(float r, float g, float b, float a=1.0);

        Sprite * manipulate_handles;
        Sprite * selected_manipulator;
        void RenderManipulator();

    public:

    GLFrame(wxWindow *parent, wxGLContext * glContext=NULL, const int* gl_attrib=NULL);

    ~GLFrame();

    bool Init();           ///Initialize OpenGL
    bool Render();         ///Draw Routine
    bool animPass();       ///An Animation Pass
    bool getStartAnim();   ///Returns to see if if animation is active
    void calcFPS();        ///Calculates the Frames per second

    void LoadTexMng(texMng * texture_manager);  ///Set the texture manager
    void LoadSceneManager(std::vector<entityManager*> * scene_manager);
    void BindPropertyWindow(propertyWindow * property_window);

    void SetPaintMode(bool b);
    void Reset();

    frameEvent  * getFrameEvent();
    wxGLContext * GetContext();
    Camera * GetCamera();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnChar(wxKeyEvent& event);
    void OnChar2(wxKeyEvent& event);
    void OnEnterWindow(wxMouseEvent& event);
    void OnMouseEvent(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);
    void onIdle(wxIdleEvent & event);

};


#endif
