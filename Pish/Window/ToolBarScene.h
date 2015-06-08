#ifndef TOOLBARSCENE_H
#define TOOLBARSCENE_H

#include "../Common/GLee.h"
#include <wx/toolbar.h>
#include <wx/image.h>
#include <wx/menu.h>
#include <wx/glcanvas.h>

#include "../Dialogs/entityDupDlg.h"

class GLFrame;
class projectTreeView;

class ToolBarScene : public wxToolBar
{
    DECLARE_EVENT_TABLE()

    private:

        projectTreeView * tree_view;
        GLFrame         * glFrame;

        wxMenu *objectsmenu;
        wxMenu *duplicatemenu;
        wxMenu *paintmenu;

    public:

        ToolBarScene(wxWindow * parent = NULL, wxWindowID id = wxID_ANY);
        ~ToolBarScene();

        void BindTreeView(projectTreeView * tree_view);
        void BindGLFrame(GLFrame * glFrame);

        void ToolEvent(wxCommandEvent & event);
        void ToolMenuEvent(wxCommandEvent & event);
};

#endif // TOOLBARSCENE_H
