#ifndef OGLWIN_H
#define OGLWIN_H

#include "../Common/GLee.h"

#include <wx/toolbar.h>
#include <wx/sysopt.h>
#include <wx/splitter.h>

#include "../Core/GLFrame.h"
#include "../Management/entityManager.h"
#include "../Window/ToolBarScene.h"
#include "../Window/projectTreeView.h"

class OGLWin : public wxSplitterWindow
{
    DECLARE_EVENT_TABLE()

    private:

        SceneManager * scene_manager;
        texMng       * texture_manager;
        wxGLContext  * opengl_context;
        GLFrame      * m_glContext;
        ToolBarScene * toolbar;

        projectTreeView * tree_view;


    public:

    OGLWin(wxWindow * parent, texMng * tMng, entityManager * entity_manager, std::vector<entityManager*> * scene_manager);
    ~OGLWin();

    void InitContext();
    void BindToolBar(ToolBarScene * toolbar);
    void BindTreeView(projectTreeView * tree_view);
    void BindPropertyWindow(propertyWindow * property_window);
    frameEvent * getFrameEvent();

    void OnSize(wxSizeEvent& event);
    void OnEnterWindow(wxMouseEvent& event);
    void SashChange(wxSplitterEvent & event);

    wxGLContext * GetContext();
    Camera * GetCamera();
    void ResetGL();

};




#endif
